//Ariel Enrique Nuñez Velazquez
//K130637

#include <iostream>
#include <vector>

using namespace std;

const int MAXSUBJECT=50;

// Registro para las fechas
struct Date{
    int day;
    int month;
    int year;
};

// Registro para las frases épicas
struct Phrase{
    string text;
    Date date;
    int rating;
};

// Registro para los profesores
struct Teacher{
    string name;
    string nickname;
    char subject[MAXSUBJECT];
    int rating;
    vector<Phrase> listPhrases;
};

// Registro para los cursos
struct AcademicYear{
    int id;
    vector<Teacher> listTeachers;
};

// Tipos de error posibles
enum Error{
    ERR_OPTION,
    ERR_EMPTY,
    ERR_DUPLICATED,
    ERR_NOT_EXIST,
    ERR_RATING
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch(e){
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY: cout << "ERROR: empty string" << endl;
            break;
        case ERR_DUPLICATED: cout << "ERROR: duplicated value" << endl;
            break;
        case ERR_NOT_EXIST: cout << "ERROR: value does not exist" << endl;
            break;
        case ERR_RATING: cout << "ERROR: number out of range" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu(){
    cout << "1- Add academic year" << endl
         << "2- Delete academic year" << endl
         << "3- Add teacher" << endl
         << "4- Delete teacher" << endl
         << "5- Show teacher" << endl
         << "6- Add phrase" << endl
         << "7- Summary" << endl
         << "q- Quit" << endl
         << "Option: ";
}

void addAcademicYear(vector<AcademicYear> &listaAños);
void deleteAcademicYear(vector<AcademicYear> &listaAños);
void addTeacher(vector<AcademicYear> &listaAños);
void deleteTeacher(vector<AcademicYear> &listaAños);
void showTeacher(const vector<AcademicYear> &listaAños);
void addPhrase(vector<AcademicYear> &listaAños);
void summary(vector<AcademicYear> &listYears);

// Función principal. Tendrás que añadir más código tuyo
int main(){
    char option;
    vector<AcademicYear> listaAños;
    
    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
                addAcademicYear(listaAños);
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
                deleteAcademicYear(listaAños);
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
                addTeacher(listaAños);
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
                deleteTeacher(listaAños);
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
                showTeacher(listaAños);
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
                addPhrase(listaAños);
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
                summary(listaAños);
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
void addAcademicYear(vector<AcademicYear> &listaAños){
    string numAux;
    AcademicYear AuxAY;
    int AñoC, isT;

    do{
        isT=0;
        cout<<"Enter academic year:"<< endl;
        getline(cin,numAux);
        if(numAux.empty()){
            error(ERR_EMPTY);
            return; //forzar la salida de la funcion
        }
        if(listaAños.size()== 0){
            AñoC=stoi(numAux);
            AuxAY.id=AñoC;
            listaAños.push_back(AuxAY);
        }
        else{
            AñoC=stoi(numAux);
            for(int i=0;i < (int)listaAños.size() && isT!=1;i++){
                if(listaAños[i].id == AñoC){
                    error(ERR_DUPLICATED);
                    isT=1;
                }
            }
            if(isT==0){
                AuxAY.id=AñoC;
                listaAños.push_back(AuxAY);
            }
        }    
    }
    while(isT==1);
}

void deleteAcademicYear(vector<AcademicYear> &listaAños){
    string numAux;
    int isT,AñoC;
    do{
        isT=0;
        cout<<"Enter academic year:"<< endl;
        getline(cin,numAux);
        if(numAux.empty()){
            error(ERR_EMPTY);
            return; //forzar la salida de la funcion
        }
        if(listaAños.size() == 0){
            error(ERR_NOT_EXIST); //esto es en caso de que el vector este vacio
            isT=0;
        }
        else{
            AñoC=stoi(numAux);
            for(int i=0;i < (int)listaAños.size();i++){
                if(listaAños[i].id == AñoC){
                    listaAños.erase(listaAños.begin()+i); //borra el vector en la posicion i
                    isT=1;
                }
            }
            if(isT==0){
              error(ERR_NOT_EXIST);  //En el caso de que el valor no este pero la cadena no este vacia
            }
        } 
    }
    while(isT==0);
}

void addTeacher(vector<AcademicYear> &listaAños){ 
    string numAux; 
    Teacher AuxT;
    int isT,isT2,AñoC,pos,raT; 
    string strSubj; 
    string strRat; 
    do{
        isT=0;
        isT2=1;
        cout<<"Enter academic year:"<< endl;
        getline(cin,numAux);
        if(numAux.empty()){
            error(ERR_EMPTY);
            return; //forzar la salida de la funcion
        }
        if(listaAños.size()== 0){ 
            error(ERR_NOT_EXIST);
        }
        else{
            AñoC=stoi(numAux);
            for(int i=0;i < (int)listaAños.size() && isT!=1;i++){ 
                if(listaAños[i].id == AñoC){
                    isT=1;
                    pos=i; 
                }
            }
            if(isT==0){
                error(ERR_NOT_EXIST);
            }
        }
    }
    while(isT==0);
    if(isT==1){
        do{
            cout<<"Enter teacher name:"<< endl;
            getline(cin,AuxT.name);

            if(listaAños[pos].listTeachers.size()== 0){
                isT2=0;
            }
            else{
                for(int i=0;i < (int)listaAños[pos].listTeachers.size() && isT2!=1;i++){
                    if(listaAños[pos].listTeachers[i].name == AuxT.name){
                        error(ERR_DUPLICATED);
                        isT2=1;
                    } 
                }
            }
        }
        while(isT2==1);
        if(isT2==0){ 
            cout<<"Enter teacher nickname:"<< endl; 
            getline(cin,AuxT.nickname);
            cout<<"Enter subject:";
            getline(cin, strSubj);

            if(strSubj.empty()){
                error(ERR_EMPTY);
            }
            else{
                int i;
                for(i = 0; i < (int)strSubj.size() && i < 49; i++){
                    AuxT.subject[i] = strSubj[i];
                } 
                AuxT.subject[i] = '\0'; //agregamos el caracter nulo al final del string
                int erRat = 0;
                do{
                    cout<<"Enter rating:";
                    getline(cin, strRat);

                    if(strRat.empty()){
                        AuxT.rating = 0;
                        erRat = 0;
                    }
                    else{
                        raT = stoi(strRat);
                        if(raT >= 1 && raT <= 5){
                            AuxT.rating = raT; 
                            erRat = 0;
                        }
                        else{
                            error(ERR_RATING);
                            erRat = 1;
                        }
                    }
                }while(erRat == 1);

            listaAños[pos].listTeachers.push_back(AuxT);
            }
        }
    }
}

void deleteTeacher(vector<AcademicYear> &listaAños){
    string strName;
    int isT = 0;

    for(int i = 0; i < (int)listaAños[0].listTeachers.size(); i++){
        cout<<listaAños[0].listTeachers[i].name<<endl;
    }
    do{
        cout<<"Enter teacher name:";
        getline(cin, strName);

        if(strName.empty()){
            error(ERR_EMPTY);
            return; //forzar la salida de la funcion
        }
        else{
            for(int i = 0; i <(int)listaAños.size(); i++){
                for(int j = 0; j<(int)listaAños[j].listTeachers.size(); j++){
                    if(listaAños[i].listTeachers[j].name == strName){
                        listaAños[i].listTeachers.erase(listaAños[i].listTeachers.begin() + j);
                        isT = 1;
                    }
                }
            }
            if(isT == 0){
                error(ERR_NOT_EXIST);
            }
        }
    }
    while(isT == 0);
}

void showTeacher(const vector<AcademicYear> &listaAños){
    string strName;
    int isT = 0;
    
    do{
        cout<<"Enter teacher name:";
        getline(cin, strName);

        if(strName.empty()){
            error(ERR_EMPTY);
            return; //forzar la salida de la funcion
        }
        else{
            for(int i = 0; i <(int)listaAños.size(); i++){
                for(int j = 0; j<(int)listaAños[j].listTeachers.size(); j++){
                    if(listaAños[i].listTeachers[j].name == strName){
                        cout<<"Name: "<<listaAños[i].listTeachers[j].name<<endl;
                        if(listaAños[i].listTeachers[j].nickname != ""){
                        cout<<"Nickname: "<<listaAños[i].listTeachers[j].nickname<<endl;
                        }
                        cout<<"Subject: "<<listaAños[i].listTeachers[j].subject<<endl;
                        cout<<"Rating:";
                        if(listaAños[i].listTeachers[j].rating != 0){
                            for(int k = 0; k < listaAños[i].listTeachers[j].rating; k++){ //imprime el rating con *
                                cout<<"*";
                            }
                        }

                        for(int k = 0; k < (int)listaAños[i].listTeachers[j].listPhrases.size(); k++){ //imprime las frases
                            cout<<"Phrase: "<<listaAños[i].listTeachers[j].listPhrases[k].text<<endl;
                            if(listaAños[i].listTeachers[j].listPhrases[k].date.day > 0){
                                cout<<"("<<listaAños[i].listTeachers[j].listPhrases[k].date.day<<"-";
                                cout<<listaAños[i].listTeachers[j].listPhrases[k].date.month<<"-";
                                cout<<listaAños[i].listTeachers[j].listPhrases[k].date.year<<")"<<endl;
                            }
                            if(listaAños[i].listTeachers[j].listPhrases[k].rating > 0){
                                cout<<"Rating:"<<"["<<listaAños[i].listTeachers[j].listPhrases[k].rating<<"]"<<endl;
                            }
                        }
                        isT = 1;
                    }
                }
            }
            if(isT == 0){
                error(ERR_NOT_EXIST);
            }
        }
    }
    while(isT == 0);
}

void addPhrase(vector<AcademicYear> &listaAños){
    string strName;
    Phrase AuxP;
    string strTx, strD,
    strM,strY,strRat,strDay;
    int d, m, y, raT,isT,conT=0,i,j,k;
    do{ // Bucle para introducir el nombre del profesor
        isT = 0; 

        cout << "Enter teacher name: ";
        getline(cin, strName); 

        if(strName.empty()){ 
            error(ERR_EMPTY); 
            isT = 0;
            return; // Se fuerza la salida de la función
        }
 
        if(listaAños.size() == 0){ // Si el vector está vacío, se muestra un mensaje de error       
            error(ERR_NOT_EXIST); 
        } 
        else{ 
            for( i = 0; i < (int)listaAños.size() && isT !=0; i++){ // Se recorre el vector para comprobar si existe el profesor
                for( j = 0; j < (int)listaAños[i].listTeachers.size() && !isT; j++){ 
                    if(listaAños[i].listTeachers[j].name == strName){ 
                        cout << "Enter phrase: "; 
                        getline(cin, strTx); // Se introduce la frase con getline 

                        if(strTx.empty()){
                            error(ERR_EMPTY); 
                            isT = 0;
                            return; // Se fuerza la salida de la función
                        } 
                        else{
                            AuxP.text = strTx; // Se introduce la frase en el registro
                            cout << "Enter date (year-month-day):"; 
                            getline(cin, strD); // Se introduce la fecha con getline para evitar problemas con el buffer de teclado

                            if(strD.empty()){
                                AuxP.date.year = 0;
                                AuxP.date.month = 0;
                                AuxP.date.day = 0;
                            } 
                            else{
                                for( k = 0; k < (int)strD.size() && conT < 2; k++){
                                    if(strD[k] == '-' && conT == 0){
                                        conT++;
                                        strY = strD.substr(0, k);
                                        y = stoi(strY);
                                        AuxP.date.year = y;
                                    }
                                    else if(strD[k] == '-' && conT == 1){
                                        conT++;
                                        strM = strD.substr(strY.size() + 1, k - strD.size() - 1);
                                        m = stoi(strM);
                                        AuxP.date.month = m;
                                        strDay = strD.substr(k + 1, strD.size() - k - 1);
                                        d = stoi(strDay);
                                        AuxP.date.day = d;
                                    } 
                                }
                            }

                            do{
                                cout << "Enter rating: "; 
                                getline(cin, strRat); // Se introduce la puntuación

                                if(strRat.empty()){
                                    raT = 0;
                                }
                                else{
                                    raT = stoi(strRat);
                                }

                                if(raT < 1 || raT > 10){
                                    error(ERR_RATING); // Se muestra un mensaje de error
                                }
                                else{
                                    AuxP.rating = raT; 
                                    listaAños[i].listTeachers[j].listPhrases.push_back(AuxP); // Se añade la frase al vector
                                        isT= 1; 
                                }
                            } while(raT < 0 || raT > 10); 
                        }
                    }
                }
            }
        }
    } while(isT != 0); 
}

void summary(vector<AcademicYear> &listaAños) {
    int Size = listaAños.size(); // Tamaño del vector
    int i,j,k,isT; 
    string strAs; 
    AcademicYear AuxAY; 
    if (Size == 0) { // Si el vector está vacío, se muestra un mensaje de error
        error(ERR_NOT_EXIST); 
        return; 
    }

    for(i = 0; i <  Size - 1; i++){ // Se recorre el vector para ordenar los cursos académicos
        for(j = 0; i  < Size - i - 1; j++){ // Se recorre el vector para ordenar los cursos académicos
            if(listaAños[j].id < listaAños[j + 1].id){ // Si el año del curso académico es menor que el siguiente, se intercambian
                AuxAY = listaAños[j]; // Se guarda el valor del curso académico en la variable auxiliar
                listaAños[j] = listaAños[j + 1]; // Se intercambia el valor del curso académico
                listaAños[j + 1] = AuxAY; // Se intercambia el valor del curso académico
            }
        }
    }

    for (i = 0; i < Size; i++) { // Se recorre el vector para mostrar el resumen
        isT = 0;
        for (j = 0; j < (int)listaAños[i].listTeachers.size(); j++) { // Se recorre el vector para mostrar el resumen
            if (listaAños[i].listTeachers[j].listPhrases.size() > 0) { 
                if (!isT) {
                    cout << "Academic year: " << listaAños[i].id << endl; 
                }

                for (k = 0; k < (int)listaAños[i].listTeachers[j].listPhrases.size(); k++) { // Se recorre el vector para mostrar las frases del profesor
                    cout << listaAños[i].listTeachers[j].name; // Se muestra el nombre del profesor

                    if (listaAños[i].listTeachers[j].listPhrases[k].rating != 0) { // Si el rating de la frase no es 0, se muestra
                        cout << " - "
                            << listaAños[i].listTeachers[j].listPhrases[k].rating // Se muestra el rating de la frase
                            << " - ";
                    }
                    else { 
                        cout << " - "; // Se muestra dos puntos y un espacio
                    }
                    cout << listaAños[i].listTeachers[j].listPhrases[k].text << endl; 
                }
                isT = 1; 
            }
        }
    }
}
