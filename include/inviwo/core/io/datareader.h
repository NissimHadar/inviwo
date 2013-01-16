#ifndef IVW_DATAREADER_H
#define IVW_DATAREADER_H

#include "inviwo/core/inviwo.h"

namespace inviwo {

class DataReader {

public:
    DataReader();
    virtual ~DataReader();

    std::string getIdentifier() const;

protected:

    void setIdentifier(const std::string& name);

private:
    std::string identifier_;
};

} // namespace

#endif // IVW_DATAREADER_H
