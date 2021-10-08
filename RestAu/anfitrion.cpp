#include "anfitrion.h"
#include "ui_anfitrion.h"
#include "iniciosesion.h"

#define STR_EQUAL 0
Anfitrion::Anfitrion(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Anfitrion)
{
    this->id=id;
    this->id.toUInt();
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    /*Mesa.prepare("Select estado from mesa where idMesa=1;");
    Mesa.exec();*/
}

Anfitrion::~Anfitrion()
{
    delete ui;
}

void Anfitrion::on_Disponibilidad_Mesas_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void Anfitrion::on_salida_clicked()
{
    close();
    InicioSesion *regresa= new InicioSesion();
    regresa->show();
}

void Anfitrion::on_Mesa_1_clicked()
{
    conexion.open();
    QString MesaD="Disponible";
    QString MesaND="No Disponible";
    QSqlQuery Mesa;
    Mesa.prepare("Select estado from mesa where idMesa=1;");
    Mesa.exec();
    //int x = QString::compare(Mesa.Value(0), MesaD, Qt::CaseInsensitive)
    //ui->Mesa_1->setStyleSheet("QPushButton { background-color: #FFFF00; }")
    if(Mesa.next()){
        QString disponibilidad=Mesa.value(0).toString();
        if(QString::compare(MesaD, disponibilidad) == STR_EQUAL){
            ui->Mesa_1->setStyleSheet("QPushButton { background-color: #008000; }");
        }
        if(QString::compare(MesaND, disponibilidad) == STR_EQUAL){
            ui->Mesa_1->setStyleSheet("QPushButton { background-color: #FF0000; }");
        }
    }

    QSqlQuery mesa2;
    mesa2.prepare("Select u.idUsuario,m.estado,u.nombre,u.apellidoMaterno,u.apellidoPaterno from mesa as m inner join usuario as u on m.mesero_idMesero=u.idUsuario where idMesa=1;");
    mesa2.exec();
    if(mesa2.next() && mesa2.value(1).toString() == "No Disponible")
    {
        ui->lineEdit->setText(mesa2.value(0).toString());
        ui->lineEdit_2->setText(mesa2.value(2).toString());
        ui->lineEdit_3->setText(mesa2.value(3).toString());
    }
    else
    {
        QMessageBox Message1;
       Message1.setText("¿Desea asignar el mesero seleccionado a la mesa seleccionada?");
       QAbstractButton * Aceptar = Message1.addButton("Aceptar",QMessageBox::AcceptRole);
        QAbstractButton * Cancelar = Message1.addButton("Cancelar",QMessageBox::NoRole);
       Message1.setIcon(QMessageBox::Information);

       Message1.exec();

        if(Message1.clickedButton() == Aceptar){

        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        qDebug() << "asignar un mesero";
        QSqlQuery asignarMesero;
        asignarMesero.prepare("select u.idusuario,u.nombre,m.estado from usuario as u inner join mesero as m on u.idUsuario=m.idMesero where m.estado='Disponible' limit 1;");
        asignarMesero.exec();
        asignarMesero.next();
        QSqlQuery CambiarValoresMesa;
        CambiarValoresMesa.prepare("update mesa set estado = 'No Disponible', mesero_idMesero='"+asignarMesero.value(0).toString()+"'where idMesa=1;");
        CambiarValoresMesa.exec();
        CambiarValoresMesa.next();
        QSqlQuery CambiarValoresMesero;
        CambiarValoresMesero.prepare("update mesero set estado = 'No Disponible' where idMesero= '"+asignarMesero.value(0).toString()+"'");
        CambiarValoresMesero.exec();
        CambiarValoresMesero.next();
    }
}

}

void Anfitrion::on_Mesa_2_clicked()
{

    conexion.open();
    QString MesaD="Disponible";
    QString MesaND="No Disponible";
    QSqlQuery Mesa;
    Mesa.prepare("Select estado from mesa where idMesa=2;");
    Mesa.exec();
    //int x = QString::compare(Mesa.Value(0), MesaD, Qt::CaseInsensitive)
    //ui->Mesa_1->setStyleSheet("QPushButton { background-color: #FFFF00; }")
    if(Mesa.next()){
        QString disponibilidad=Mesa.value(0).toString();
        if(QString::compare(MesaD, disponibilidad) == STR_EQUAL){
            //ui->lineEdit->setStyleSheet("QLineEdit { background-color: #008000; }");
            ui->Mesa_2->setStyleSheet("QPushButton { background-color: #008000; }");
        }
        if(QString::compare(MesaND, disponibilidad) == STR_EQUAL){
            ui->Mesa_2->setStyleSheet("QPushButton { background-color: #FF0000; }");
        }
    }
    QSqlQuery mesa2;
    mesa2.prepare("Select u.idUsuario,m.estado,u.nombre,u.apellidoMaterno,u.apellidoPaterno from mesa as m inner join usuario as u on m.mesero_idMesero=u.idUsuario where idMesa=2;");
    mesa2.exec();
    if(mesa2.next() && mesa2.value(1).toString() == "No Disponible")
    {
        ui->lineEdit->setText(mesa2.value(0).toString());
        ui->lineEdit_2->setText(mesa2.value(2).toString());
        ui->lineEdit_3->setText(mesa2.value(3).toString());
    }
    else
    {
        QMessageBox Message2;
        Message2.setText("¿Desea asignar el mesero seleccionado a la mesa seleccionada?");
        QAbstractButton * Acep = Message2.addButton("Aceptar",QMessageBox::AcceptRole);
        QAbstractButton * Can = Message2.addButton("Cancelar",QMessageBox::NoRole);
        Message2.setIcon(QMessageBox::Information);

        Message2.exec();

        if(Message2.clickedButton() == Acep){

        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        qDebug() << "asignar un mesero";
        QSqlQuery asignarMesero;
        asignarMesero.prepare("select u.idusuario,u.nombre,m.estado from usuario as u inner join mesero as m on u.idUsuario=m.idMesero where m.estado='Disponible' limit 1;");
        asignarMesero.exec();
        asignarMesero.next();
        QSqlQuery CambiarValoresMesa;
        CambiarValoresMesa.prepare("update mesa set estado = 'No Disponible', mesero_idMesero='"+asignarMesero.value(0).toString()+"'where idMesa=2;");
        CambiarValoresMesa.exec();
        CambiarValoresMesa.next();
        QSqlQuery CambiarValoresMesero;
        CambiarValoresMesero.prepare("update mesero set estado = 'No Disponible' where idMesero= '"+asignarMesero.value(0).toString()+"'");
        CambiarValoresMesero.exec();
        CambiarValoresMesero.next();
        }
    }
}

void Anfitrion::on_Mesa_3_clicked()
{

    conexion.open();
    QString MesaD="Disponible";
    QString MesaND="No Disponible";
    QSqlQuery Mesa;
    Mesa.prepare("Select estado from mesa where idMesa=3;");
    Mesa.exec();
    //int x = QString::compare(Mesa.Value(0), MesaD, Qt::CaseInsensitive)
    //ui->Mesa_1->setStyleSheet("QPushButton { background-color: #FFFF00; }")
    if(Mesa.next()){
        QString disponibilidad=Mesa.value(0).toString();
        if(QString::compare(MesaD, disponibilidad) == STR_EQUAL){
            ui->Mesa_3->setStyleSheet("QPushButton { background-color: #008000; }");
        }
        if(QString::compare(MesaND, disponibilidad) == STR_EQUAL){
            ui->Mesa_3->setStyleSheet("QPushButton { background-color: #FF0000; }");
        }
    }

    QSqlQuery mesa2;
    mesa2.prepare("Select u.idUsuario,m.estado,u.nombre,u.apellidoMaterno,u.apellidoPaterno from mesa as m inner join usuario as u on m.mesero_idMesero=u.idUsuario where idMesa=3;");
    mesa2.exec();
    if(mesa2.next() && mesa2.value(1).toString() == "No Disponible")
    {
        ui->lineEdit->setText(mesa2.value(0).toString());
        ui->lineEdit_2->setText(mesa2.value(2).toString());
        ui->lineEdit_3->setText(mesa2.value(3).toString());
    }
    else
    {
        QMessageBox Message3;
        Message3.setText("¿Desea asignar el mesero seleccionado a la mesa seleccionada?");
        QAbstractButton * Acep = Message3.addButton("Aceptar",QMessageBox::AcceptRole);
        QAbstractButton * Nope = Message3.addButton("Cancelar",QMessageBox::NoRole);
        Message3.setIcon(QMessageBox::Information);

        Message3.exec();

        if(Message3.clickedButton() == Acep){

        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        qDebug() << "asignar un mesero";
        QSqlQuery asignarMesero;
        asignarMesero.prepare("select u.idusuario,u.nombre,m.estado from usuario as u inner join mesero as m on u.idUsuario=m.idMesero where m.estado='Disponible' limit 1;");
        asignarMesero.exec();
        asignarMesero.next();
        QSqlQuery CambiarValoresMesa;
        CambiarValoresMesa.prepare("update mesa set estado = 'No Disponible', mesero_idMesero='"+asignarMesero.value(0).toString()+"'where idMesa=3;");
        CambiarValoresMesa.exec();
        CambiarValoresMesa.next();
        QSqlQuery CambiarValoresMesero;
        CambiarValoresMesero.prepare("update mesero set estado = 'No Disponible' where idMesero= '"+asignarMesero.value(0).toString()+"'");
        CambiarValoresMesero.exec();
        CambiarValoresMesero.next();
    }
    }
}

void Anfitrion::on_Mesa_4_clicked()
{
    conexion.open();
    QString MesaD="Disponible";
    QString MesaND="No Disponible";
    QSqlQuery Mesa;
    Mesa.prepare("Select estado from mesa where idMesa=4;");
    Mesa.exec();
    //int x = QString::compare(Mesa.Value(0), MesaD, Qt::CaseInsensitive)
    //ui->Mesa_1->setStyleSheet("QPushButton { background-color: #FFFF00; }")
    if(Mesa.next()){
        QString disponibilidad=Mesa.value(0).toString();
        if(QString::compare(MesaD, disponibilidad) == STR_EQUAL){
            ui->Mesa_4->setStyleSheet("QPushButton { background-color: #008000; }");
        }
        if(QString::compare(MesaND, disponibilidad) == STR_EQUAL){
            ui->Mesa_4->setStyleSheet("QPushButton { background-color: #FF0000; }");
        }
    }
    QSqlQuery mesa2;
    mesa2.prepare("Select u.idUsuario,m.estado,u.nombre,u.apellidoMaterno,u.apellidoPaterno from mesa as m inner join usuario as u on m.mesero_idMesero=u.idUsuario where idMesa=4;");
    mesa2.exec();
    if(mesa2.next() && mesa2.value(1).toString() == "No Disponible")
    {
        ui->lineEdit->setText(mesa2.value(0).toString());
        ui->lineEdit_2->setText(mesa2.value(2).toString());
        ui->lineEdit_3->setText(mesa2.value(3).toString());
    }
    else
    {
        QMessageBox Message4;
        Message4.setText("¿Desea asignar el mesero seleccionado a la mesa seleccionada?");
        QAbstractButton * Accept = Message4.addButton("Aceptar",QMessageBox::AcceptRole);
        QAbstractButton * Denied = Message4.addButton("Cancelar",QMessageBox::NoRole);
        Message4.setIcon(QMessageBox::Information);

        Message4.exec();

        if(Message4.clickedButton() == Accept){


        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        qDebug() << "asignar un mesero";
        QSqlQuery asignarMesero;
        asignarMesero.prepare("select u.idusuario,u.nombre,m.estado from usuario as u inner join mesero as m on u.idUsuario=m.idMesero where m.estado='Disponible' limit 1;");
        asignarMesero.exec();
        asignarMesero.next();
        QSqlQuery CambiarValoresMesa;
        CambiarValoresMesa.prepare("update mesa set estado = 'No Disponible', mesero_idMesero='"+asignarMesero.value(0).toString()+"'where idMesa=4;");
        CambiarValoresMesa.exec();
        CambiarValoresMesa.next();
        QSqlQuery CambiarValoresMesero;
        CambiarValoresMesero.prepare("update mesero set estado = 'No Disponible' where idMesero= '"+asignarMesero.value(0).toString()+"'");
        CambiarValoresMesero.exec();
        CambiarValoresMesero.next();

    }
    }
}
