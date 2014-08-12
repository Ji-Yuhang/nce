#include "data.hxx"
Data* Data::g_data = 0;
Data::Data(QObject *parent) :
    QObject(parent)
{
    g_data =this;
}

Data *Data::instance()
{
    return g_data;
}
