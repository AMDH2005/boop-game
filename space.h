#include <string>
#include <iomanip>

#ifndef SPACE_H
#define SPACE_H

class space {
    public:
        
        space() {status = "empty";}

        std::string getStatus() const { return status; }

        void setEmpty() { status = "empty"; }

        void setBP() { status = "BP"; }

        void setBD() { status = "BD"; }

        void setRP() { status = "RP"; }

        void setRD() { status = "RD"; }

        bool isEmpty() const { return status == "empty"; }

        bool isBP() const { return status == "BP"; }

        bool isBD() const { return status == "BD"; }

        bool isRP() const { return status == "RP"; }

        bool isRD() const { return status == "RD"; }

        void operator=(const space &other) {status = other.getStatus();}

        bool operator==(const space &other) {return status == other.getStatus();}



    private:
        std::string status;
    
};

#endif