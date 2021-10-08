#include "iniciosesion.h"
#include "ui_iniciosesion.h"
#include "gerente.h"
#include "anfitrion.h"
#include "mesero.h"
#include "cocinero.h"

InicioSesion::InicioSesion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InicioSesion)
{
    ui->setupUi(this);
    conexion = QSqlDatabase::addDatabase("QODBC");
    conexion.setPort(3306);
    conexion.setHostName("root");
    conexion.setPassword("");
    conexion.setDatabaseName("restaurant");

    if(conexion.open())
        qDebug()<< "Conexión EXITOSA";
    else
        qDebug()<< "Conexión FALLIDA";

    conexion.close();
}

InicioSesion::~InicioSesion()
{
    delete ui;
}


void InicioSesion::on_pushButton_clicked()
{

    conexion.open();
    QString ID;
    QString Contra;
    //gerente *aux= new gerente();
   // aux->show();
    //close();
    ID = ui->CodigoID->text();
    Contra = ui->Contrasena->text();

    if(ID == ""){
        //Error por si no ha ingresado nada en el campo
        //qDebug() << "Por favor ingrese una opcion. ";
        QMessageBox::critical(this,"Error","Por favor, inserte su ID.","Aceptar");
        return;
    }

    if(Contra == ""){
        //Error por si no ha ingresado nada en el campo
        //qDebug() << "Por favor ingrese una opcion. ";
        QMessageBox::critical(this,"Error","Por favor, inserte su contraseña.","Aceptar");
        return;
    }

    //login mesero
    if(ui->Mesero->isChecked()){
        QSqlQuery Mesero;
        Mesero.prepare("Select idusuario, password from usuario inner join mesero on idusuario = idmesero where idmesero='"+ID+"' and password ='"+Contra+"' ;");
        Mesero.exec();
        //vamos a buscar los datos
        if(Mesero.next()){
      //        qDebug() << "ID : " << mesero.value(0);
    //          qDebug() << "Password: " << mesero.value(1);
              //Vamos a verificar la conexion
              if(Mesero.value(0) == ID && Mesero.value(1) == Contra){
                         qDebug() << "Pudiste entrar al sistema. Bienvenido." ;
                         mesero *InterMes = new mesero(ID.toInt());
                         InterMes->show();
                         close();
              }
        }
    }

    //login anfitrion
    if(ui->Anfitrion->isChecked()){
        QSqlQuery anfitrion;
        anfitrion.prepare("Select idusuario, password from usuario inner join anfitrion on idusuario = idanfitrion where idanfitrion='"+ID+"' and password ='"+Contra+"' ;");
        anfitrion.exec();
        //vamos a buscar los datos
        if(anfitrion.next()){
    //          qDebug() << "ID : " << Anfitrion.value(0);
        //      qDebug() << "Password: " << Anfitrion.value(1);

              //Vamos a verificar la conexion
              if(anfitrion.value(0) == ID && anfitrion.value(1) == Contra){
                         qDebug() << "Pudiste entrar al sistema. Bienvenido." ;
                         Anfitrion *interAnfi = new Anfitrion(ID.toInt());
                         interAnfi->show();
                         close();
              }
        }
    }

    //login cocinero
    if(ui->Cocinero->isChecked()){
        QSqlQuery Cocinero;
        Cocinero.prepare("Select idusuario, password from usuario inner join cocinero on idusuario = idcocinero where idcocinero='"+ID+"' and password ='"+Contra+"' ;");
        Cocinero.exec();
        //vamos a buscar los datos
        if(Cocinero.next()){
    //          qDebug() << "ID : " << Anfitrion.value(0);
        //      qDebug() << "Password: " << Anfitrion.value(1);

              //Vamos a verificar la conexion
              if(Cocinero.value(0) == ID && Cocinero.value(1) == Contra){
                         qDebug() << "Pudiste entrar al sistema. Bienvenido." ;
                         cocinero *interCoci = new cocinero(ID.toInt());
                         interCoci->show();
                         close();
              }
        }
    }

    //login gerente
    if(ui->Gerente->isChecked()){
        QSqlQuery Gerente;
        Gerente.prepare("Select idusuario, password from usuario inner join gerente on idusuario = idgerente where idgerente='"+ID+"' and password ='"+Contra+"' ;");
        Gerente.exec();
        //vamos a buscar los datos
        if(Gerente.next()){
    //          qDebug() << "ID : " << Anfitrion.value(0);
        //      qDebug() << "Password: " << Anfitrion.value(1);

              //Vamos a verificar la conexion
              if(Gerente.value(0) == ID && Gerente.value(1) == Contra){
                      //   qDebug() << "Pudiste entrar al sistema. Bienvenido." ;
                  gerente *aux= new gerente();
                  aux->show();
                  close();
              }
        }
    }

    /*
    //Se va a hacer el query de busqueda dentro del sistema
    QSqlQuery Login;
    Login.prepare("Select idusuario, password from usuario where idusuario='"+ID+"' and password ='"+Contra+"' ;");
    Login.exec();
    //busca dentro del query
    if(Login.next()){
      //  qDebug() << "ID : " << Login.value(0);
      //  qDebug() << "Password: " << Login.value(1);
          //Si los valores coinciden tanto en la base como en los line edit
        if(Login.value(0) == ID && Login.value(1) == Contra){
            qDebug() << "Pudiste entrar al sistema. Bienvenido." ;
        }
    }
    */
}
