#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <vector>


using namespace std;

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;

// Registro para las preguntas
struct Question{
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// Registro para los profesores
struct Teacher{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// Registro para la base de datos
struct Database{
    unsigned int nextId;
    vector<Question> questions;
    vector<Teacher> teachers;
};

// Tipos de errores posibles
enum Error {
    ERR_OPTION,
    ERR_EMPTY,
    ERR_UNIT,
    ERR_CHAR,
    ERR_FILE,
    ERR_NAME,
    ERR_DUPLICATED,
    ERR_PASSWORD,
    ERR_NO_QUESTIONS,
    ERR_ID,
    ERR_ARGS
};


void addQuestion(Database &data, int &numData);
void batchAddQuestions(Database &data, int &numData);
void deleteQuestion(Database &base);
void addTeacher(Database &data);
void addAnswers(Database &data);
void viewAnswers(Database &data);
void viewStatistics(Database &base);
void exportQuestions(Database &data);
void addBinTeachers(Database &data);
void loadTeachers(Database &data);
void comprobarNom(Database &data, string &nombre, bool &nombreCorrecto, bool &rn);
void validarFila(string &linea, int &tipoError, int &contador, bool &hayError);
void convertirCon(string &contrasenya);
void batchAddQuestionsComando(Database &data, int &numData, const char *fileRef);
void summary(int numLinea, int lineaError, int preguntasAñadidas, int &numData, int &errorN);
void error(Error e);
void showMenu();















/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch (e){
        case ERR_OPTION:
            cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY:
            cout << "ERROR: empty string" << endl;
            break;
        case ERR_UNIT:
            cout << "ERROR: wrong unit" << endl;
            break;
        case ERR_CHAR:
            cout << "ERROR: wrong char" << endl;
            break;
        case ERR_FILE:
            cout << "ERROR: cannot open file" << endl;
            break;
        case ERR_NAME:
            cout << "ERROR: wrong teacher name" << endl;
            break;
        case ERR_DUPLICATED:
            cout << "ERROR: duplicated name" << endl;
            break;
        case ERR_PASSWORD:
            cout << "ERROR: wrong password" << endl;
            break;      
        case ERR_NO_QUESTIONS:
            cout << "ERROR: no pending questions" << endl;
            break;
        case ERR_ID:
            cout << "ERROR: wrong id" << endl;
            break;
        case ERR_ARGS:
            cout << "ERROR: wrong arguments" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu() {
    cout << "1- Add question" << endl
         << "2- Batch add questions" << endl
         << "3- Delete question" << endl
         << "4- Add teacher" << endl
         << "5- Add answers" << endl
         << "6- View answers" << endl
         << "7- View statistics" << endl
         << "8- Export questions" << endl
         << "q- Quit" << endl
         << "Option: ";
}

// Función principal. Tendrás que añadir más código tuyo
// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[]) {
    Database data;
    int numData = 1,
        recorredor,
        recorredor2,
        recorredor3,
        contarF = 0,
        contarS = 0;
    data.nextId= numData;
    char option;
    string fileName;

    loadTeachers(data);

    for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){
        numData = data.questions[recorredor].id;
    }


    
    for (recorredor3 = 1; recorredor3 < argc; recorredor3++) {
        if (recorredor3 > 1 && strcmp(argv[recorredor3 - 1], "-f") == 0) {
            continue; // Ignorar el nombre del archivo de preguntas
        }
        if (strcmp(argv[recorredor3], "-s") != 0 && strcmp(argv[recorredor3], "-f") != 0) {
           error(ERR_ARGS); 
           return 0;
        }
    }


    for (recorredor = 1; recorredor < argc; recorredor++) {
        if (strcmp(argv[recorredor], "-f") == 0) {
            contarF++;
            
            if(contarF == 3){
                error(ERR_ARGS);
                return 0;
            }

            if (contarF == 1) {
                  if (strcmp(argv[recorredor + 1], "-f") == 0 || strcmp(argv[recorredor + 1], "-s") != 0){
                    fileName = argv[recorredor + 1];
                    contarF++;
                  }
                  else if (strcmp(argv[recorredor + 1], "-s") == 0){
                    error(ERR_ARGS);
                    return 0;
                  }     
            }
        }
    }




    for (recorredor2 = 1; recorredor2 < argc; recorredor2++) {
        if (strcmp(argv[recorredor2], "-s") == 0) {
            contarS++;
        }

    }

    if(contarF < 3 && contarF > 0){
        batchAddQuestionsComando(data, numData, fileName.c_str());
    }

    if(contarS == 1){
        viewStatistics(data);
    }





    do{
        showMenu();
        cin >> option;
        cin.get();
        
        switch(option){
            case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
                addQuestion(data, numData);
                break;
            case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
                batchAddQuestions(data, numData);
                break;
            case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta
                deleteQuestion(data);
                break;
            case '4': // Llamar a la función "addTeacher" para añadir un nuevo profesor
                addTeacher(data);
                break;
            case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                addAnswers(data);
                break;
            case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
                viewAnswers(data);
                break;
            case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
                viewStatistics(data);
                break;
            case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
                exportQuestions(data);
                break;
            case 'q': // Salir del programa guardando los profesores en fichero
                break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');

  return 0;
}



void addQuestion(Database &data, int &numData){
    Question pregunta; // Pregunta a añadir
    string unitStr, // Unidad de la pregunta en formato string
        preguntaStr; // Pregunta a añadir a la base de datos en formato string
    int numero; // Unidad de la pregunta en formato entero
    bool unitCorrecto, // Comprueba si la unidad es correcta
        preguntaCorrecta; // Comprueba si la pregunta es correcta
    


    do{ //-----------------------------------------------------------------------------
        unitCorrecto = false; // Inicializamos la variable a false

        cout << "Enter unit:";
        getline(cin, unitStr);

        if (unitStr.empty()) { // Comprobamos si la unidad está vacía
            error(ERR_EMPTY);
            return;
        }

        try { // Convertimos la unidad a entero
            numero = stoi(unitStr);
            unitCorrecto = true;
        } 
        catch (const std::invalid_argument& e) {// Si no se puede convertir a entero, mostramos un error
            error(ERR_UNIT);
        }

        if(unitCorrecto){// Si la unidad es correcta, comprobamos que esté entre 1 y 5
            if (numero < 1 || numero > 5) { // Comprobamos si la unidad está entre 1 y 5
                error(ERR_UNIT);// Si no está entre 1 y 5, mostramos un error
                unitCorrecto = false;
            }
        }
    } while (!unitCorrecto); // Si la unidad no es correcta, volvemos a pedirla

    if(unitCorrecto){ // Si la unidad es correcta, pedimos la pregunta -----------------------------------------------------------------------------
        do{ // Pedimos la pregunta hasta que sea correcta
            preguntaCorrecta = false;

            cout << "Enter question:";
            getline(cin, preguntaStr);
            
            if(preguntaStr.empty()){ // Comprobamos si la pregunta está vacía
                error(ERR_EMPTY);
                return;
            }

            if(preguntaStr.find("|") != string::npos){ // Comprobamos si la pregunta contiene el carácter '|'
                error(ERR_CHAR); // Si contiene el carácter '|', mostramos un error
            }
            else{
                preguntaCorrecta = true; // Si no contiene el carácter '|', la pregunta es correcta
            }
        }
        while(!preguntaCorrecta); // Si la pregunta no es correcta, volvemos a pedirla

        if(preguntaCorrecta){
            data.nextId = numData; // Asignamos el id a la base de datos

            pregunta.id = data.nextId; // Asignamos el id a la pregunta
            pregunta.unit = numero; // Asignamos la unidad a la pregunta
            pregunta.question = preguntaStr; // Asignamos la pregunta a la pregunta
            data.questions.push_back(pregunta); // Añadimos la pregunta a la base de datos
            numData++; // Aumentamos el id para la siguiente pregunta

        }
    }
}



void batchAddQuestions (Database &data, int &numData){
    string fileName, // Nombre del fichero
        linea; // Línea del fichero
    int numLinea = 0, // Número de línea
        tipoError = 0, // Tipo de error
        contador,
        lineaError = 0,
        preguntasAñadidas = 1,
        errorN;
    bool equivocado,
        hayError;
    do{
        equivocado = false;

        cout << "Enter filename: ";
        getline(cin, fileName);

        if(fileName.empty()){ // Comprobamos si el nombre del fichero está vacío
            error(ERR_EMPTY); // Si está vacío, mostramos un error
            return;
        }

        ifstream file(fileName); // Abrimos el fichero

        if (file.is_open()){ // Comprobamos si no se ha podido abrir el fichero
            errorN = 0;

            for(; getline(file, linea);){ // Leemos el fichero línea a línea
                numLinea++; // Aumentamos el número de línea
                
                validarFila(linea, tipoError, contador, hayError); // Validamos la línea

                if(tipoError == 1){
                    errorN++;
                }

                if(hayError && tipoError != 1){ // Si hay un error, mostramos el error
                    cout << "Error line " << numLinea << endl;
                    lineaError++;
                }
                if(!hayError){ // Si no hay errores, añadimos la pregunta a la base de datos
                    if(contador == 2){
                        Question pregunta;
                        size_t pos1, pos2;

                        pos1 = linea.find('|');
                        pos2 = linea.find('|', pos1 + 1);

                        pregunta.unit = stoi(linea.substr(0, pos1));
                        pregunta.question = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                        pregunta.answer = linea.substr(pos2 + 1);
                        pregunta.id = preguntasAñadidas;

                        data.questions.push_back(pregunta);
                        preguntasAñadidas++;
                    }
                    else if(contador == 1){
                        Question pregunta;
                        size_t pos1;

                        pos1 = linea.find('|');

                        pregunta.unit = stoi(linea.substr(0, pos1));
                        pregunta.question = linea.substr(pos1 + 1);
                        pregunta.id = preguntasAñadidas;

                        data.questions.push_back(pregunta);
                        preguntasAñadidas++;

                    }
                }
            }

            summary(numLinea, lineaError, preguntasAñadidas, numData, errorN); // Mostramos el resumen de las preguntas añadidas


            file.close(); // Cerramos el fichero
        }
        else{
            error(ERR_FILE); // Mostramos el error ERR_FILE
            equivocado = true;
        }
    }
    while(equivocado);
}



void summary(int numLinea, int lineaError, int preguntasAñadidas, int &numData, int &errorN){
    if(numLinea == 0){ // Comprobamos si el fichero está vacío
        cout << "Summary: 0/0 questions added" << endl;
    }
    else{
        cout << "Summary: " << numLinea - lineaError - errorN << "/" << numLinea - errorN << " questions added" << endl;
        numData = preguntasAñadidas;
    }
}



void deleteQuestion(Database &base){
    string id;
    int idInt,
        recorredor;
    bool equivocado;

    do{
        equivocado = false;
        cout << "Enter question id: ";
        getline(cin, id);

        if(id.empty()){
            error(ERR_EMPTY);   
            return;
        }

        try{
            idInt = stoi(id);
        }
        catch(const std::invalid_argument&){
            error(ERR_ID);
            equivocado = true;
        }

        if(!equivocado){
            for(recorredor = 0; recorredor < (int)base.questions.size(); recorredor++){
                if((int)base.questions[recorredor].id == idInt){
                    base.questions.erase(base.questions.begin() + recorredor);
                    return;
                }
            }
            error(ERR_ID);
            equivocado = true;
        }

    }
    while(equivocado);

}



void addTeacher(Database &data){
    Teacher profesor;
    string nombre,
        contrasenya;
    int recorredor,
        errorContra;
    bool nombreCorrecto,
        passwordCorrecto,
        rn = false;

    comprobarNom(data, nombre, nombreCorrecto, rn);

    if(rn){
        return;
    }

    if(nombreCorrecto){
        do{
            passwordCorrecto = false;
            errorContra = 0;

            cout << "Enter password:";
            getline(cin, contrasenya);

            if (contrasenya.empty()) {
                error(ERR_EMPTY);
                return;
            }

            for(recorredor = 0; recorredor < (int)contrasenya.size() && errorContra == 0; recorredor++){
                if(isdigit(contrasenya[recorredor])){
                    passwordCorrecto = true;
                }
                else{
                    error(ERR_PASSWORD);
                    errorContra++;
                }
            }

            if(passwordCorrecto){
                if(contrasenya.size() != 4){
                    error(ERR_PASSWORD);
                    passwordCorrecto = false;
                }
            }

        } while (!passwordCorrecto);

        if(passwordCorrecto){
            convertirCon(contrasenya);

            strcpy(profesor.name, nombre.c_str());
            strcpy(profesor.password, contrasenya.c_str());
            profesor.answered = 0;
            data.teachers.push_back(profesor);
        }
    }
}



void addAnswers(Database &data){
    int recorredor,
        posEncontrada,
        noContestadas,
        id,
        idRespondido;
    bool encontrado,
        correcto,
        idCorrecto,
        idConvertido,
        respuestaCorrecta;
    string nombre,
        contrasenya,
        idStr,
        respuesta;
    
    do{
        cout << "Enter teacher name: ";
        getline(cin, nombre);

        if(nombre.empty()){
            error(ERR_EMPTY);
            return;
        }

        encontrado = false;

        if(!nombre.empty()){
            if(data.teachers.size() != 0){
                encontrado = false;

                for(recorredor = 0; recorredor < (int)data.teachers.size() && !encontrado; recorredor++){
                    if(nombre == data.teachers[recorredor].name){
                        encontrado = true;
                        posEncontrada = recorredor;
                    }
                }
            }
        }

        if(!encontrado){
            error(ERR_NAME);
        }
    }
    while(!encontrado);

    if(encontrado){

        do{
            correcto = false;
            
            cout << "Enter password: ";
            getline(cin, contrasenya);

            if(contrasenya.empty()){
                error(ERR_EMPTY);
                return;
            }

            convertirCon(contrasenya);

            if(contrasenya != data.teachers[posEncontrada].password){
                error(ERR_PASSWORD);
            }

            if(contrasenya == data.teachers[posEncontrada].password){
                correcto = true;
            }
        }
        while(!correcto);
    }


    do{
        if(correcto){
            noContestadas = 0;

            for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){
                if(data.questions[recorredor].answer.empty()){
                    cout << data.questions[recorredor].id << ". (" << data.questions[recorredor].unit << ") " << data.questions[recorredor].question << endl;
                    noContestadas++;
                }
            }

            if(noContestadas == 0){
                error(ERR_NO_QUESTIONS);
                return;
            }

            if(noContestadas > 0){
                do{
                    idCorrecto = false;
                    idConvertido = false;

                    cout << "Enter question id: ";
                    getline(cin, idStr);

                    if(idStr.empty()){
                        error(ERR_EMPTY);
                        return;
                    }

                    if(idStr == "b"){
                        return;
                    }

                    if(idStr != "b"){
                        try{
                            id = stoi(idStr);
                            idConvertido = true;
                        }
                        catch(const std::invalid_argument&){
                            error(ERR_ID);
                        }
                    }

                    if(idConvertido){
                    for(recorredor = 0; recorredor < (int)data.questions.size() && !idCorrecto; recorredor++){
                            if(data.questions[recorredor].answer.empty() && (int)data.questions[recorredor].id == id){
                                idCorrecto = true;
                                idRespondido = recorredor;
                            }
                        }

                        if(!idCorrecto){
                            error(ERR_ID);
                        }

                    }
                    
                } 
                while(!idCorrecto);


                if(idCorrecto){
                    do{
                        respuestaCorrecta = true;

                        cout << "Enter answer: ";
                        getline(cin, respuesta);

                        if(respuesta.empty()){
                            error(ERR_EMPTY);
                            return;
                        }

                        if (respuesta.find('|') != string::npos) {
                            error(ERR_CHAR);
                            respuestaCorrecta = false;
                        }
                    }
                    while(!respuestaCorrecta);

                    if(respuestaCorrecta){
                        data.questions[idRespondido].answer = respuesta;
                        data.teachers[posEncontrada].answered++;
                    }
                }
            }
        }
    }
    while(idStr != "b");
}



void viewAnswers(Database &data){
    int recorredor;

    for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){
        if(!data.questions[recorredor].answer.empty()){
            cout << data.questions[recorredor].id << ". (" 
            << data.questions[recorredor].unit << ") " 
            << data.questions[recorredor].question << ": "
            << data.questions[recorredor].answer << endl;
        }
    }
}



void viewStatistics(Database &base){
    int recorredor,\
        contadorPreguntas = 0,
        contadorRespuestas = 0;

    if(base.questions.size() != 0){
        for(recorredor = 0; recorredor < (int)base.questions.size(); recorredor++){
            contadorPreguntas++;

            if(!base.questions[recorredor].answer.empty()){
                contadorRespuestas++;
            }
        }
    }
    else{
        cout << "Total number of questions: 0" << endl;
        cout << "Number of questions answered: 0" << endl;  

        for(recorredor = 0; recorredor < (int)base.teachers.size(); recorredor++){
            cout << base.teachers[recorredor].name << ": " << base.teachers[recorredor].answered << endl;
        }


    }

    if(contadorRespuestas != 0 && contadorPreguntas != 0){
        cout << "Total number of questions: " << contadorPreguntas << endl;
        cout << "Number of questions answered: " << contadorRespuestas << endl;

        for(recorredor = 0; recorredor < (int)base.teachers.size(); recorredor++){
            cout << base.teachers[recorredor].name << ": " << base.teachers[recorredor].answered << endl;
        }



    }
    else if(contadorRespuestas == 0 && contadorPreguntas != 0){
        cout << "Total number of questions: " << contadorPreguntas << endl;
        cout << "Number of questions answered: 0" << endl;

        for(recorredor = 0; recorredor < (int)base.teachers.size(); recorredor++){
            cout << base.teachers[recorredor].name << ": " << base.teachers[recorredor].answered << endl;
        }

    }
}



void exportQuestions(Database &data){
    string filename;
    bool noAbierto;
    int recorredor;
    
    do{
        noAbierto = false;

        cout << "Enter filename: ";
        getline(cin, filename);
    
        if(filename.empty()){
            error(ERR_EMPTY);
            return;
        }

        ofstream file(filename);

        if(file){
            for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){
                if(data.questions[recorredor].answer.empty()){
                    file << data.questions[recorredor].unit << "|" << data.questions[recorredor].question << endl;
                }
                else{
                    file << data.questions[recorredor].unit << "|" << data.questions[recorredor].question << "|" << data.questions[recorredor].answer << endl;
                }
            }
            file.close();
        }
        else{
            error(ERR_FILE);
            noAbierto = true;
        }
    }
    while(noAbierto);

}





void addBinTeachers(Database &data){
    ofstream file;
    int recorredor;

    
    file.open("teachers.bin", ios::binary);
    if(file.is_open()){
        for(recorredor = 0; recorredor < (int)data.teachers.size(); recorredor++){
            file.write((char*)&data.teachers[recorredor], sizeof(Teacher));
        }
        file.close();
    }else{
        error(ERR_FILE);
    }
}



void loadTeachers(Database &data){
    ifstream file;
    Teacher teacher;

    file.open("teachers.bin", ios::binary);
    if(file.is_open()){
        while(file.read((char*)&teacher, sizeof(Teacher))){
            data.teachers.push_back(teacher);
        }
        file.close();
    }
}



void comprobarNom(Database &data, string &nombre, bool &nombreCorrecto, bool &rn){
    int recorredor,
        errorCarac;

    do{
        nombreCorrecto = false;
        rn = false;

        cout << "Enter teacher name:";
        getline(cin, nombre);
        
        if(nombre.empty()){
            error(ERR_EMPTY);
            rn = true;
            return;
        }

        errorCarac = 0;
        for(recorredor = 0; recorredor < (int)nombre.size() && errorCarac == 0; recorredor++){
            if(isalpha(nombre[recorredor]) || nombre[recorredor] == ' '){
                nombreCorrecto = true;
            }
            else{
                error(ERR_NAME);
                nombreCorrecto = false;
                errorCarac++;
            }
        }

        if(nombreCorrecto){
            while(nombre[0] == ' '){
                nombre.erase(0, 1);
            }

            while(nombre[nombre.size() - 1] == ' '){
                nombre.erase(nombre.size() - 1, 1);
            }

            if(nombre.size() < 3 || nombre.size() > KMAXNAME - 1){
                error(ERR_NAME);
                nombreCorrecto = false;
            }
            
            for(recorredor = 0; recorredor < (int)data.teachers.size(); recorredor++){
                if(string(data.teachers[recorredor].name) == nombre){
                    error(ERR_DUPLICATED);
                    nombreCorrecto = false;
                }
            }
        }
    } 
    while (!nombreCorrecto);
}



void validarFila(string &linea, int &tipoError, int &contador, bool &hayError){
    size_t pos1, pos2;

    contador = 0;
    tipoError = 0;
    hayError = false;

    if(linea.empty()){ // Comprobamos si la línea está vacía
        tipoError = 1;
        hayError = true;
        return;
    }


    for(char c : linea) { // Recorremos la línea
        if(c == '|') { // si encontramos el carácter '|'
            contador++; // Aumentamos el contador
        }
    }

    if (linea.back() == '|') {
        tipoError = 4;
        hayError = true;
        return;
    }


    if(contador < 1){
        tipoError = 4;
        hayError = true;
        return;
    }

    if(contador > 2){
        tipoError = 4;
        hayError = true;
        return;
    }

    if(contador == 0){ 
        tipoError = 5;
        hayError = true;
        return;
    }


    if (contador == 2) {
        pos1 = linea.find('|');
        while (pos1 != string::npos) {
            pos2 = linea.find('|', pos1 + 1);
            if (pos2 == string::npos || pos2 - pos1 == 1) {
                tipoError = 2;
                hayError = true; // Agregar esta línea para indicar que hay un error
                return;
            }
            pos1 = linea.find('|', pos2 + 1);
        }
    }


    if(contador == 1 || contador == 2){ 
        if(linea.back() == '|'){ 
            if(contador == 2){
                tipoError = 3;
                return;
            }

        }
    }
}



void convertirCon(string &contrasenya){
    int recorredor;

    for(recorredor = 0; recorredor < (int)contrasenya.size(); recorredor++){
        switch(contrasenya[recorredor]){
            case '0':
                contrasenya[recorredor] = 'T';
                break;
            case '1':
                contrasenya[recorredor] = 'R';
                break;
            case '2':
                contrasenya[recorredor] = 'W';
                break;
            case '3':
                contrasenya[recorredor] = 'A';
                break;
            case '4':
                contrasenya[recorredor] = 'G';
                break;
            case '5':
                contrasenya[recorredor] = 'M';
                break;
            case '6':
                contrasenya[recorredor] = 'Y';
                break;
            case '7':
                contrasenya[recorredor] = 'F';
                break;
            case '8':
                contrasenya[recorredor] = 'P';
                break;
            case '9':
                contrasenya[recorredor] = 'D';
                break;
        }
    }
}




void batchAddQuestionsComando(Database &data, int &numData, const char *fileRef){
    string fileName, // Nombre del fichero
        linea; // Línea del fichero
    int numLinea = 0, // Número de línea
        tipoError = 0, // Tipo de error
        contador,
        lineaError = 0,
        preguntasAñadidas = 1,
        errorN;
    bool hayError;

        fileName = fileRef;

        ifstream file(fileName); // Abrimos el fichero

        if (file.is_open()){ // Comprobamos si no se ha podido abrir el fichero
            errorN = 0;
            
            for(; getline(file, linea);){ // Leemos el fichero línea a línea
                numLinea++; // Aumentamos el número de línea

                validarFila(linea, tipoError, contador, hayError); // Validamos la línea

                if(tipoError == 1){
                    errorN++;
                }

                if(hayError && tipoError != 1){ // Si hay un error, mostramos el error
                    cout << "Error line" << numLinea << endl;
                    lineaError++;
                }
                if(!hayError){ // Si no hay errores, añadimos la pregunta a la base de datos
                    if(contador == 2){
                        Question pregunta;
                        size_t pos1, pos2;

                        pos1 = linea.find('|');
                        pos2 = linea.find('|', pos1 + 1);

                        pregunta.unit = stoi(linea.substr(0, pos1));
                        pregunta.question = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                        pregunta.answer = linea.substr(pos2 + 1);
                        pregunta.id = preguntasAñadidas;

                        data.questions.push_back(pregunta);
                        preguntasAñadidas++;
                    }
                    else if(contador == 1){
                        Question pregunta;
                        size_t pos1;

                        pos1 = linea.find('|');

                        pregunta.unit = stoi(linea.substr(0, pos1));
                        pregunta.question = linea.substr(pos1 + 1);
                        pregunta.id = preguntasAñadidas;

                        data.questions.push_back(pregunta);
                        preguntasAñadidas++;

                    }
                }
            }


            summary(numLinea, lineaError, preguntasAñadidas, numData, errorN); // Mostramos el resumen de las preguntas añadidas
        }
        else{
            error(ERR_FILE); // Mostramos el error ERR_FILE
        }
}