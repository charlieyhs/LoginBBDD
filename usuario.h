#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario
{
public:
    Usuario(int id=-1, const QString &nombre="", const QString &password="");
    int id()const {return mId;}
    QString nombre() const {return mNombre;}
    QString password() const{return mPassword;}

    void setId(int id){mId = id;}
    void setNombre(const QString &nombre){mNombre = nombre;}
    void setPassword(const QString &password){mPassword = password;}

private:
    int mId;
    QString mNombre;
    QString mPassword;
};

#endif // USUARIO_H
