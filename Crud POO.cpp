#include <stdio.h>
#include <string>
#include<fstream>
#include<iostream>

using namespace std;

//Llamar archivo
const char *nombe_archivo = "test.dat";

//estructura de datos


class Alumnos {
	private:
		int A_codigo;
		char* A_nombre;
		char* A_apellido;
		int A_telefono;
	
	public:
	void SetCodigo(int codigo){ A_codigo = codigo; }
	void SetNombre(char* nombre){ A_nombre  = nombre;}
	void SetApellido(char* apellido){ A_apellido = apellido;}
	void SetTelefono(int telefono){ A_telefono = telefono;}

	const int GetCodigo(){return A_codigo;}
	const char* GetNombre(){return A_nombre;}
	const char* GetApellido(){return A_apellido;}
	const int GetTelefono(){return A_telefono;}
};

//Declaracion de Scope clases

void PedirDatos(Alumnos alumnos){

	int codigo_temp;
	char nombre_temp[20];
	char apellido_temp[20];
	int telefono_temp;

	printf("Introduzca el Codigo:\n");
	cin>>codigo_temp;
	alumnos.SetCodigo(codigo_temp);
	fflush( stdin );
	printf("Introduzca el Nombre:\n");
	scanf("%s", nombre_temp);
	alumnos.SetNombre(nombre_temp);
	fflush( stdin );
	printf("Introduzca el Apellido:\n");
	scanf("%s", apellido_temp);
	alumnos.SetApellido(apellido_temp);
	fflush( stdin );
	printf("Introduzca el Telefono:\n");
	cin>>telefono_temp;
	alumnos.SetTelefono(telefono_temp);
}

void IngresoDatos(){
	system("cls");
	char continuar;
	FILE* archivo = fopen(nombe_archivo, "ab");
	
	do{
		system("cls");
		Alumnos alumno;
		PedirDatos(alumno);
		fwrite(&alumno, sizeof(Alumnos), 1, archivo );
		 
		fflush( stdin );
		printf("Desea inglesar otro alumno s/n:\n");
		scanf("%c", &continuar);
	}while((continuar =='s') || (continuar=='S'));
};

void LeerDatos(){
	system("cls");
	
	FILE* archivo = fopen(nombe_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombe_archivo, "w+b");
	}
	
	Alumnos alumno;
	int registro=0;
	fread ( &alumno, sizeof(Alumnos), 1, archivo );
	do{
	   printf("Id: %i Codigo: %i Nombre: %s Apellido:  %s Telefono: %i \n",registro,alumno.GetCodigo() , alumno.GetNombre(), alumno.GetApellido(), alumno.GetTelefono());  
	     
		fread ( &alumno, sizeof(Alumnos), 1, archivo );
		registro += 1;	
	} while (feof( archivo ) == 0);
};

void borrarDatos(){
	system("cls");
	const char *nombre_archivo_temp = "archivo_temp.dat";
	Alumnos alumno;
	FILE* archivo = fopen(nombe_archivo, "rb");
	FILE* archivo_temp=fopen(nombre_archivo_temp,"w+b");
	int id=0,i=0;
	cout<<"Ingrese el ID del estudiante que desea eliminar:"<<endl; 
	cin>>id;                                                   
		while(fread(&alumno,sizeof(Alumnos),1,archivo)){
			if (i != id){
				fwrite(&alumno,sizeof(Alumnos),1,archivo_temp);
			} 
			
			i++; 
		}
	                
		fclose(archivo_temp); 
		fclose(archivo); 
	                
		archivo_temp=fopen(nombre_archivo_temp,"rb"); 
		archivo=fopen(nombe_archivo,"wb"); 
	 
		while(fread(&alumno,sizeof(Alumnos),1, archivo_temp)){ 
			fwrite(&alumno,sizeof(Alumnos),1, archivo); 
		}
	                
	fclose(archivo_temp); 
	fclose(archivo); 
	system("PAUSE");
}

void actualizarDatos(){
	system("cls");
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		string nombre,apellido;	
    	Alumnos alumno;
    
		cout << "Ingrese el ID que desea Modificar: ";
    	cin >> id;
    	fseek ( archivo, id * sizeof(Alumnos), SEEK_SET );
	
		PedirDatos(alumno);
		
		fwrite( &alumno, sizeof(Alumnos), 1, archivo );
		
	fclose(archivo);
	system("PAUSE");
}

int main(){
	int opcion;
	

		cout<<"------ MENU ------"<<endl;
		cout<<"1. Ingresar"<<endl;
		cout<<"2. Listado"<<endl;
		cout<<"3. Actualizar"<<endl;
		cout<<"4. Eliminar"<<endl;
		cout<<"5.Salir"<<endl;
		cin>>opcion;

		switch(opcion){
			case 1:{
					IngresoDatos();
				break;
				}
			
			 case 2:{
				LeerDatos();	
				break;
				}
			
			case 3:{
				actualizarDatos();	
				break;
				}
					
			case 4:{
				borrarDatos();	
				break;
				} 
			
			case 5:{
				exit(0);
				break;
				}
			}
	
	return 0;
}
