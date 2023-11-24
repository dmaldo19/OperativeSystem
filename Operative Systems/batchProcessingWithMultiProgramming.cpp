//Diego Alberto Maldonado Melendez
//Actividad 05 programa 2

#include <iostream>
#include <windows.h> //Libreria para limpiar pantalla, 
#include <queue> //Para usar cola, estructura de datos utilizada
#include <iomanip> //Libreria para definir cuantos decimales mostrar en la impresion
#include <random> //Libreria para generar valores random
#include <conio.h> //Libreria para kbhit
#include <string>

using namespace std;

//Definicion de mi clase proceso, con los atributos requeridos de ID,
//operacion, tiempoMaximo, tiempoTranscurrido, Lote y resultado
class proceso{
    private:
        int id;
        string operacion;
        int tiempoMaximo;
        int tiempoTranscurrido;
        int lote;
        double result;

    //Metodos principalmente de asignacion y retorno, get y set.
    public:
        proceso(int i, const string &o, int t, int tt, int l, double r)
        : result(r){
            setId(i);
            setOperacion(o);
            setTiempoMaximo(t);
            setTiempoTranscurrido(tt);
            setLote(l);
        }

        void setId(int i){
            id = ( i < 0 ) ? 0 : i;
        }

        int getId() const{
            return id;
        }

        void setLote(int l){
            lote = l;
        }

        int getLote() const{
            return lote;
        }


        void setOperacion(const string &o){
            operacion = o;
        }

        string getOperacion() const{
            return operacion;
        }

        void setTiempoMaximo(int t){
            tiempoMaximo = (t < 0) ? 0: t;
        }

        int getTiempoMaximo() const{
            return tiempoMaximo;
        }

        void setTiempoTranscurrido(int tt){
            tiempoTranscurrido = (tt < 0) ? 0: tt;
        }

        int getTiempoTranscurrido() const{
            return tiempoTranscurrido;
        }

        void setResult(double r){
            result = r;
        }

        double getResult() const{
            return result;
        }

};

// Función para posicionar el cursor en la pantalla
//C++ no tiene gotoxy nativa, por lo que encontre una funcion que pude implementar
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Esta funcion permite que la terminal se ponga en pantalla completa cuando se inicie la ejecucion
void setConsoleToFullscreen() {
    HWND console = GetConsoleWindow();
    if (console != NULL) {
        ShowWindow(console, SW_MAXIMIZE); // Maximiza la ventana de la consola
        Sleep(100); // Pequeña pausa para permitir que la ventana se maximice completamente
    }
}

//Funcion para la realizacion de las operaciones, teniendo resultado double para
// divisiones principalmente
double computingOperation(int option, int a, int b){
    
    double result;
    switch (option){
        case 1: //Suma
            result = a + b;
            break;
        case 2: //Resta
            result = a - b;
            break;
        case 3: //Multiplicacion
            result = a * b;
            break;
        case 4: //Division
            result = static_cast<double>(a)/b;
            break;
        case 5: //Residuo
            result = a % b;
            break;
        case 6: //Porcentaje
            result = (a * b)/100;
            break;

        default:
            break;
    }
    return result;
}

//Prototipo de funciones que iba a requerir posteriormente
void ProcesoEnEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera);
proceso procesoEnEjecucion(queue<proceso>& EnEspera);
int lotesPendientes(queue<proceso>& total);
void impresionesDeProcesos(queue<proceso>& total, queue<proceso>& espera, queue<proceso>& final, int& contador);

//Mi main
int main(){
    setConsoleToFullscreen(); //Invoco a que se ponga la pantalla completa
    int totalProcess = 0; //Todos los procesos que ingreso el usuario
    int batch = 1; //Numero de lote de cada proceso
    int counter = 0; //Contador para asignar el numero de lote 
    queue<proceso> colaProcesos; //cola principal que almacenara todos los procesos
    gotoxy(0, 0); cout << "-----Programa de simulacion de procesamiento por lote-----";
    gotoxy(0, 2); cout << "Ingrese la cantidad de procesos a realizar: ";
    cin >> totalProcess;

    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister 19937 como generador

    // Definir la primera distribución (por ejemplo, de -50 a 50)
    uniform_int_distribution<int> distribucionOperacion(1, 6);
    uniform_int_distribution<int> distribucionTiempo(6, 18);

    while(totalProcess < 1){ //Validacion por si no se meten procesos
        gotoxy(0, 4); cout << "Debe haber al menos un proceso. Intente nuevamente: ";
        cin >> totalProcess;
    }

    //Ciclo para pedir los datos
    for(int i = 1; i <= totalProcess; i++){
        system("cls");
        int id, operacion, tiempoMaximo;
        uniform_int_distribution<int> distribucion(-10, 10);
        // Crear un generador de números aleatorios
        random_device rd;
        mt19937 gen(rd()); // Mersenne Twister 19937 como generador
        int a = distribucion(gen);
        int b = distribucion(gen);
        string signo;
        double result;
        //bool idRepetido;
        id = i;
        /*do {
            idRepetido = false; // Restablece la bandera a falso
            id = i;

            // Verifica si el ID ya existe en la cola
            queue<proceso> copiaCola = colaProcesos; // Crea una copia de la cola
            //Validacion de si ya existe un ID como el ingresado
            while (!copiaCola.empty()) {
                proceso p = copiaCola.front();
                copiaCola.pop();

                if (p.getId() == id) {//Mi objeto p, de tipo proceso, es el que recorre la cola
                    idRepetido = true; //Si ya esta el ID, lo pide nuevamente 
                    gotoxy(0, 2); cout << "El ID ingresado ya existe en la cola. Intente nuevamente: ";
                    break; // Si se encuentra un ID repetido, muestra un mensaje y vuelve a pedir el ID
                }
            }
        } while (idRepetido);*/

        operacion = distribucionOperacion(gen);
        
        switch (operacion)
        {
        case 1:
            signo = to_string(a) + "+" + to_string(b);
            break;
        case 2:
            signo = to_string(a) + "-" + to_string(b);
            break;
        case 3:
            signo = to_string(a) + "*" + to_string(b);
            break;
        case 4:
            while (b == 0){
                    b = distribucion(gen);
                }
            signo = to_string(a) + "/" + to_string(b);
            break;
        case 5:
            while (b == 0){
                    b = distribucion(gen);
                }
            signo = to_string(a) + "%" + to_string(b);
            break;
        case 6:
            signo = to_string(a) + "P" + to_string(b);
            break;
        default:
            break;
        }
        result = computingOperation(operacion, a, b);//Invoco mi funcion para que realice la operacion
        tiempoMaximo = distribucionTiempo(gen);
        
        if(counter < 5){//Me permite controlar que numero de lote tendra el proceso que esta siendo capturado
            counter ++;
        } else{
            batch ++;
            counter = 1;
        }

        //Instancio mi objeto proceso y se lo añado a la cola
        proceso nuevoProceso(id, signo, tiempoMaximo, 0, batch, result);
        colaProcesos.push(nuevoProceso);
    }

    //Creo las colas que necesitare para evaluar realizar los procesos
    queue<proceso> EnEspera, Terminado;

    //Tiempo total del programa
    int tiempo = 0;

    //Ciclo que se ejecutara hasta que la cola de procesos este vacia
    while(!colaProcesos.empty()){
        //Lleno la cola de procesos en espera con el lote correspondiente
        ProcesoEnEspera(colaProcesos, EnEspera);
        //Ciclo para ejecutar todos los procesos en la lista de espera
        while (!EnEspera.empty()){
            system("cls");
            impresionesDeProcesos(colaProcesos, EnEspera, Terminado, tiempo); //Invoco funcion para mostrarlos
            queue<proceso> auxiliarTerminados = Terminado;
            //Imprimo nuevamente debido a errores con el system("cls")
            int yf = 8;
            int finCicloF = auxiliarTerminados.size();
            for(int i = 0; i < finCicloF; i++){
                proceso elementoFinal = auxiliarTerminados.front();
                gotoxy(40+5, yf); cout << elementoFinal.getId();
                gotoxy(46+5, yf); cout << elementoFinal.getOperacion();
                if(elementoFinal.getResult()!= -77.0){
                    gotoxy(53+5, yf); cout << fixed << setprecision(1) << elementoFinal.getResult();
                } else {
                    gotoxy(53+5, yf); cout << "ER";
                }
                gotoxy(60+5, yf); cout << elementoFinal.getLote();
                yf++;
                auxiliarTerminados.pop();
            }
        }
    }
    //Final del main
    gotoxy(15,20); cout << "Tiempo total: " << tiempo;
    gotoxy(15,30); cout << "Programa Finalizado..." << endl;
    system("pause");
    return 0;
}

//Funcion que permite determinar cuales procesos pasaran a la lista de esperas
void ProcesoEnEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera) {
    if (totalProcesos.empty()) {
        return; // No hay elementos en totalProcesos, no se puede hacer nada
    }

    int loteEnEspera = totalProcesos.front().getLote(); // Obtener el lote del primer proceso
    queue<proceso> auxiliar = totalProcesos;

    //Todos los procesos del mismo lote pasan, es decir, si la lista esta llena, los del lote 1 pasara.
    //Si ya se ejecutaron los del 1er lote, pasan los del 2do, y asi sucesivamente
    while (!auxiliar.empty()) {
        proceso elementoCorrespondiente = auxiliar.front();
        if (elementoCorrespondiente.getLote() == loteEnEspera) {
            enEspera.push(elementoCorrespondiente);
            auxiliar.pop();
        }else{
            break;
        }
    }
}


//Funcion que sirve para saber cual es el proceso que se va a ejecutar, tomando en cuenta la lista de espera
proceso procesoEnEjecucion(queue<proceso>& EnEspera){
    proceso enEjecucion = EnEspera.front();
    //EnEspera.pop();
    return enEjecucion;
}

//Funcion que me permite saber cuantos lotes faltan
int lotesPendientes(queue<proceso>& total){
    proceso elemento1 = total.front();
    proceso elemento2 = total.back();
    int loteInicial = elemento1.getLote();
    int loteFinal = elemento2.getLote();
    return loteFinal-loteInicial;
}

//Funcion para imprimir todos los procesos
void impresionesDeProcesos(queue<proceso>& total, queue<proceso>& espera, queue<proceso>& final, int& contador) {
    proceso enEjecucion = procesoEnEjecucion(espera);
    espera.pop();
    gotoxy(0,2); cout << "----------------------Ejecucion de procesos-------------------------";
    gotoxy(0,4); cout << "N. De lotes pendiente: " << lotesPendientes(total);
    //Procesos en espera
    gotoxy(0,6); cout << "Lote Actual";
    gotoxy(0,7); cout << "ID  TME  TT";
    //Terminados
    gotoxy(45, 6); cout << ("Terminados");
    gotoxy(40+5, 7); cout << ("ID");
    gotoxy(46+5, 7); cout << ("Ope");
    gotoxy(53+5, 7); cout << ("Res");
    gotoxy(60+5, 7); cout << ("N.L");

    queue<proceso> auxiliarTerminados = final;
    int yf = 8;
    int finCicloF = auxiliarTerminados.size();
    for(int i = 0; i < finCicloF; i++){
        proceso elementoFinal = auxiliarTerminados.front();
        gotoxy(40+5, yf); cout << elementoFinal.getId();
        gotoxy(46+5, yf); cout << elementoFinal.getOperacion();
        if(elementoFinal.getResult()!= -77.0){
            gotoxy(53+5, yf); cout << fixed << setprecision(1) << elementoFinal.getResult();
        } else {
            gotoxy(53+5, yf); cout << "ER";
        }
        gotoxy(60+5, yf); cout << elementoFinal.getLote();
        yf++;
        auxiliarTerminados.pop();
    }

    //Procesos en espera
    int y = 8;
    queue<proceso> auxiliar = espera;
    int finCicloI = auxiliar.size();
    for(int i = 0; i < finCicloI; i++){
        proceso elementoEspera = auxiliar.front();
        gotoxy(0, y); cout << elementoEspera.getId();
        gotoxy(4, y); cout << elementoEspera.getTiempoMaximo(); 
        gotoxy(9, y); cout << elementoEspera.getTiempoTranscurrido();
        auxiliar.pop();
        y++;
    }

    //Proceso en ejecucion
    for (int i = enEjecucion.getTiempoTranscurrido(); i < enEjecucion.getTiempoMaximo(); i++){
        gotoxy(15,20); cout << "Tiempo total: " << contador;
        gotoxy(15,6); cout << "Proceso en ejecucion";
        gotoxy(15,7); cout << "ID: " << enEjecucion.getId();
        gotoxy(15,8); cout << "Ope: "<< enEjecucion.getOperacion();
        gotoxy(15,9); cout << "TME: " << enEjecucion.getTiempoMaximo();
        gotoxy(15,10); cout << "TT: " << i << "  ";
        gotoxy(15,11); cout << "TR: " << enEjecucion.getTiempoMaximo() - i << "  ";
        // Espera hasta que el cronómetro avance un segundo
        enEjecucion.setTiempoTranscurrido(i + 1);
        Sleep(1000);
        contador++;
        if(kbhit()){
            char key = getch();
            switch (key)
            {
                case 'i':
                    i = enEjecucion.getTiempoMaximo();
                    break;
                case 'e':
                    i = enEjecucion.getTiempoMaximo();
                    enEjecucion.setTiempoTranscurrido(enEjecucion.getTiempoMaximo());
                    enEjecucion.setResult(-77);
                    break;
                case 'p':
                    while (1){
                        if(kbhit()){
                            key = getch();
                            if (key == 'c'){
                                break;
                            }
                        }
                    }
                default:
                    break;
            }
        }
    }
    if(enEjecucion.getTiempoTranscurrido() < enEjecucion.getTiempoMaximo()){
        espera.push(enEjecucion);
    } else{
        total.pop();
        final.push(enEjecucion);
    }
    gotoxy(15,6); cout << "Proceso en ejecucion";
    gotoxy(15,7); cout << "ID:    ";
    gotoxy(15,8); cout << "Ope:    ";
    gotoxy(15,9); cout << "TME:    ";
    gotoxy(15,10); cout << "TT:    ";
    gotoxy(15,11); cout << "TR:    ";

}