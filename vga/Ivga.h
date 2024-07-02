#ifndef ivga_h
#define ivga_h

class IVGA
{
private:
public:
    ~IVGA(){};
    // sends the next data line
    static void sendNextLine();
    // sends an blank black line
    static void sendBlank();

    //! TEST
    //implement as you wish
    virtual void fill();
    //implement as you wish
    virtual void fillDifferent();
};

#endif