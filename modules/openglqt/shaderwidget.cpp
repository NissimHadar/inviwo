/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2015-2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#include <modules/openglqt/shaderwidget.h>

#include <modules/opengl/shader/shaderobject.h>
#include <modules/opengl/shader/shaderresource.h>
#include <modules/opengl/shader/shadermanager.h>
#include <modules/qtwidgets/properties/syntaxhighlighter.h>
#include <modules/qtwidgets/inviwoqtutils.h>
#include <inviwo/core/util/filesystem.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QTextEdit>
#include <QDialog>
#include <QToolBar>
#include <QMainWindow>
#include <QMenuBar>
#include <QGridLayout>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QFont>
#include <warn/pop>

namespace inviwo {

ShaderWidget::ShaderWidget(const ShaderObject* obj, QWidget* parent)
    : InviwoDockWidget(utilqt::toQString(obj->getFileName()), parent, "ShaderEditorWidget")
    , obj_(obj) {

    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    resize(QSize(500, 700));  // default size
    setFloating(true);
    setSticky(false);

    QMainWindow* mainWindow = new QMainWindow();
    mainWindow->setContextMenuPolicy(Qt::NoContextMenu);
    QToolBar* toolBar = new QToolBar();
    mainWindow->addToolBar(toolBar);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    setWidget(mainWindow);

    auto shadercode = new QTextEdit(nullptr);
    shadercode->setObjectName("shaderwidgetcode");
    shadercode->setReadOnly(false);
    shadercode->setText(utilqt::toQString(obj->print(false, false)));
    shadercode->setWordWrapMode(QTextOption::NoWrap);
    auto syntaxHighlighter =
        SyntaxHighligther::createSyntaxHighligther<GLSL>(shadercode->document());

    QFont fixedFont("Monospace");
    fixedFont.setPointSize(10);
    fixedFont.setStyleHint(QFont::TypeWriter);
    shadercode->setFont(fixedFont);

    QColor bgColor = syntaxHighlighter->getBackgroundColor();

    // select monospace font family and set background color matching syntax highlighting
    QString styleSheet(QString("QTextEdit { font-family: 'monospace'; background-color: %1; }")
                           .arg(bgColor.name()));
    shadercode->setStyleSheet(styleSheet);

    auto save = toolBar->addAction(QIcon(":/icons/save.png"), tr("&Save shader"));
    save->setShortcut(QKeySequence::Save);
    save->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    mainWindow->addAction(save);
    connect(save, &QAction::triggered, [=]() {
        if (auto fr = dynamic_cast<const FileShaderResource*>(obj->getResource().get())) {
            auto file = filesystem::ofstream(fr->file());
            file << utilqt::fromQString(shadercode->toPlainText());
            file.close();
        } else if (auto sr = dynamic_cast<const StringShaderResource*>(obj->getResource().get())) {
            // get the non-const version from the manager.
            auto res = ShaderManager::getPtr()->getShaderResource(sr->key());
            if (auto editable = dynamic_cast<StringShaderResource*>(res.get())) {
                editable->setSource(utilqt::fromQString(shadercode->toPlainText()));
            }
        }
    });

    auto showSource = toolBar->addAction("Show Sources");
    showSource->setChecked(false);
    showSource->setCheckable(true);

    auto preprocess = toolBar->addAction("Show preprocess");
    preprocess->setChecked(false);
    preprocess->setCheckable(true);

    auto update = [=](int /*state*/) {
        shadercode->setText(obj->print(showSource->isChecked(), preprocess->isChecked()).c_str());
        shadercode->setReadOnly(showSource->isChecked() || preprocess->isChecked());
        save->setEnabled(!showSource->isChecked() && !preprocess->isChecked());
        showSource->setText(showSource->isChecked() ? "Hide Sources" : "Show Sources");
        preprocess->setText(preprocess->isChecked() ? "Hide Preprocessed" : "Show Preprocessed");
    };

    connect(showSource, &QAction::triggered, update);
    connect(preprocess, &QAction::triggered, update);

    mainWindow->setCentralWidget(shadercode);

    loadState();
}

ShaderWidget::~ShaderWidget() = default;

void ShaderWidget::closeEvent(QCloseEvent* event) {
    saveState();
    event->accept();
    emit widgetClosed();
    this->deleteLater();
}

}  // namespace inviwo
