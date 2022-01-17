#include "dialog.h"
#include "ui_dialog.h"
#include "registraradmindialog.h"
#include "mainwindow.h"

#include <QCheckBox>
#include <QSqlQuery>
#include <QMessageBox>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    compruebaAdmin();
    ui->usuarioNormalRadioButton->setChecked(true);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    Usuario usu(-1,ui->usuarioLineEdit->text(),ui->passwordLineEdit->text());
    int cantidad;
    bool esUsuario;

    if(ui->usuarioNormalRadioButton->isChecked()){
        q.exec(QString("SELECT count(*) FROM usuario WHERE nombre LIKE '%1' AND password LIKE '%2'").arg(usu.nombre()).arg(usu.password()));
        q.next();
        cantidad = q.value(0).toInt();
        if(cantidad == 0){
            QMessageBox::warning(this,"AVISO","Usuario y/o Contraseña incorrecto");
            return;
        }
        esUsuario = true;
    }else{
        q.exec(QString("SELECT count(*) FROM administrador WHERE nombre like '%1' AND password LIKE '%2'").arg(usu.nombre()).arg(usu.password()));
        q.next();
        q.value(0).toInt();
        cantidad = q.value(0).toInt();
        if(cantidad == 0){
            QMessageBox::warning(this,"AVISO","Usuario y/o Contraseña incorrecto");
        }
        esUsuario = false;
    }
    if(esUsuario){
        mTipo = USUARIO;
    }else{
        mTipo = ADMINISTRADOR;
    }
    accept();

}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

void Dialog::on_registrarPushButton_clicked()
{
    RegistrarAdminDialog d(this);
    auto adminCheckBox = d.getAdminCheckBox();
    adminCheckBox->setChecked(true);
    adminCheckBox->setEnabled(false);
    if(d.exec() == QDialog::Rejected){
        return;
    }
    auto admin = d.getAdmin();
    QSqlQuery q;
    q.exec(QString("INSERT INTO administrador (nombre,password) VALUES ('%1','%2')").arg(admin.nombre()).arg(admin.password()));
    compruebaAdmin();

}

void Dialog::compruebaAdmin()
{
    QSqlQuery q;
    q.exec("SELECT count(*) FROM administrador");
    q.next();
    const int cantidadAdmins = q.value(0).toInt();
    if(cantidadAdmins == 0){
        ui->registrarPushButton->setEnabled(true);
    }else{
        ui->registrarPushButton->setEnabled(false);
    }
}
