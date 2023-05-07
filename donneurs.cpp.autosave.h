#include "donneurs.h"
#include <QSqlQuery>
#include <QtDebug>

QString donneurs::get_nom() {return nom_donneur;}
QString donneurs::get_adresse() {return adresse_donneur;}
QString donneurs::get_mail() {return mail;}
int donneurs::get_tlph() {return telephone;}
int donneurs::get_id() {return id_donneur;}

void donneurs::setnom(QString n) {nom_donneur=n;}
void donneurs::setadresse(QString n) {adresse_donneur=n;}
void donneurs::setmail(QString n) {mail=n;}
void donneurs::settlph(int n) {this->telephone=n;}
void donneurs::setid(int n) {this->telephone=n;}
donneurs::donneurs()
{
    nom_donneur="";
    adresse_donneur="";
    mail="";
    telephone=0;
}
donneurs::donneurs(QString nom_donneur ,QString adresse_donneur,QString mail,int telephone)
{
    this->nom_donneur=nom_donneur;
    this->adresse_donneur=adresse_donneur;
    this->mail=mail;
    this->telephone=telephone;
}
QSqlQueryModel * donneurs::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from donneurs");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
return model;
}
bool donneurs::supprimer(int id_donneur)
{
QSqlQuery query;
QString res=QString::number(id_donneur);
query.prepare("Delete from donneurs where id_donneur= :id_donneur");
query.bindValue(":id_donneur",res);
return query.exec();
}
bool donneurs::ajouter()
{
    QSqlQuery query1;

    QString res1 = QString::number(telephone);
    query1.prepare("INSERT INTO donneurs (nom_donneur, adresse_donneur, mail, telephone)"
                   "VALUES(:nom_donneur, :adresse_donneur, :mail, :telephone)");
    query1.bindValue(":nom", nom_donneur);
    query1.bindValue(":adresse", adresse_donneur);
    query1.bindValue(":mail", mail);
    query1.bindValue(":tel", res1);
    return query1.exec();
}
