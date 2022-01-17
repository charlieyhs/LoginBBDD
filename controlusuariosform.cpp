#include "controlusuariosform.h"
#include "ui_controlusuariosform.h"
#include "dialog.h"
#include "registraradmindialog.h"

#include <QSqlTableModel>
#include <QCheckBox>
#include <QSqlQuery>

ControlUsuariosForm::ControlUsuariosForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlUsuariosForm)
{
    ui->setupUi(this);
    mModelUsuario = new QSqlTableModel(this);
    mModelUsuario->setTable("usuario");
    mModelUsuario->select();
    mModelUsuario->setHeaderData(0,Qt::Horizontal,"Id del Usuario");
    mModelUsuario->setHeaderData(1,Qt::Horizontal,"Nombre del Usuario");
    mModelUsuario->setHeaderData(2,Qt::Horizontal,"Contraseña del Usuario");
    ui->tableViewUsuario->setModel(mModelUsuario);

    mModelAdmin = new QSqlTableModel(this);
    mModelAdmin->setTable("administrador");
    mModelAdmin->select();
    mModelAdmin->setHeaderData(0,Qt::Horizontal,"Id del Admin");
    mModelAdmin->setHeaderData(1,Qt::Horizontal,"Nombre del Admin");
    mModelAdmin->setHeaderData(2,Qt::Horizontal,"Contraseña del Admin");
    ui->tableViewAdmin->setModel(mModelAdmin);

}

ControlUsuariosForm::~ControlUsuariosForm()
{
    delete ui;
}

void ControlUsuariosForm::on_agregarPushButton_clicked()
{
    RegistrarAdminDialog d(this);

    if(d.exec() == QDialog::Rejected){
        return;
    }
    auto admin = d.getAdmin();
    QSqlQuery qry;
    qry.exec(QString("INSERT INTO %1 "
                     "(nombre,password) VALUES ('%2','%3')")
             .arg(d.getAdminCheckBox()->isChecked() ? "administrador" : "usuario")
             .arg(admin.nombre())
             .arg(admin.password()));
    mModelAdmin->select();
    mModelUsuario->select();
}


