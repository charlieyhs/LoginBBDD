#include "registraradmindialog.h"
#include "ui_registraradmindialog.h"

#include <QMessageBox>

RegistrarAdminDialog::RegistrarAdminDialog(QWidget *parent) :
    QDialog(parent)
    ,ui(new Ui::RegistrarAdminDialog)
    ,mAdmin(-1,"","")
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->repeatPasswordLineEdit->setEchoMode(QLineEdit::Password);

}

RegistrarAdminDialog::~RegistrarAdminDialog()
{
    delete ui;
}

QCheckBox *RegistrarAdminDialog::getAdminCheckBox() const
{
    return ui->adminCheckBox;
}

void RegistrarAdminDialog::on_buttonBox_accepted()
{
    mAdmin.setId(1);
    mAdmin.setNombre(ui->usuarioLineEdit->text());
    mAdmin.setPassword(ui->passwordLineEdit->text());
    if(mAdmin.password() != ui->repeatPasswordLineEdit->text()){
        QMessageBox::critical(this,"Error","Las contraseñas deben coincidir");
        return;
    }
    accept();
}

void RegistrarAdminDialog::on_buttonBox_rejected()
{
    reject();
}
