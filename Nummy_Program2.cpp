 			/*****************************************
							Integrantes
				- Maria Valentina Gonzalez Vera
				- Arturo Hung
				- Italo Visconti
				- Rafael Zappala
			*****************************************/

				/*******************************
				 *          Librerias
				*******************************/

				#include <stdio.h>
				#include <stdlib.h>
				#include <conio.h>
				#include <stdbool.h>
				#include <string.h>
				#include <ctype.h>
				#include <time.h>
				#include <unistd.h>


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			const long int maxlongint=2147483647; //maximo numero para un long int
			const int maxint=32767; // maximo numero para un int

			char vacio[2];

			 	typedef struct fechas
				{
					int anio;
					int mes;
					int dia;
				} Fechas;

				typedef struct prodinc
				{
					int codigoPrt;
					int cantidad;
					float precio;
					struct prodinc *prox;
				}  Prodinc;

				typedef struct pedidos
				{
					int factura;
					int codigoEmp;
				    fechas fechas;
					bool entregados;
					float monto_total;
					struct pedidos *prox;
					Prodinc *aba; //multilista
				} Pedidos;

			 	 typedef struct productos
				{
					int codigoPrt;
					char descripcion [21];
					long int precioUd;
					bool activo;
					struct productos *prox;
				} Productos;


				typedef struct personas
				{
					char nombre_apellido [21];
					long int cedula;
					fechas fechas;
					char ciudad [16];
					char direccion [41];
					struct personas *prox;
					Pedidos *aba; //multilista
				} Personas;

				typedef	struct empresas
					{
						int codigoEmp;
						char nombreEmp [21];
						int tipo;
						char tlf [13];
						char direccion [41];
						struct empresas *prox;
						Productos *aba; //multilista
					} Empresas;

				//////////////////////////////////////

					/****************************
					 *  Prototipos de funciones
					 ***************************/
					 
				//////Basicas//////

				void Encabezado ();                      // Rutina para imprimir el encabezado (Nombre de los integrantes)
				void BloqMayus  ( char s[] );            // Rutina para imprimir una cadena de caracteres en formato de mayuscula sostenida
				int validar_num(char numero[]);          // Funcion para validar que la cadena contiene solo numeros
				void ingfecha(int *tanio, int *tmes, int *tdia);  //Rutina para llenar las variables temporales de fecha
				void ingnombre(char *tnombre);			//Rutina para llenar el nombre
				void ingciu(char *tciudad);				//Rutina para llenar la ciudad
				void ingdir(char *tdir);				//Rutina para llenar la direccion
				void ingnum(long int *numero);			//Rutina para llenar la cedula
				void introduciropcion(int *opcion);    //Rutina para introducir opciones del menu
				void prodactivo(bool *act);			//Rutina para llenar la "actividad" de un producto
				void eliminartodoprod(Empresas **emp);	//Rutina para eliminar una lista dinamica completa de productos
				void mostrarproductosemp(Empresas *emp, int codigo); //Rutina para mostrar todos los productos de una empresa
				void eliminartodoprodinc(Pedidos **ped); //Rutina para eliminar todos los productos incluidos de un envio
				void eliminartodoenvio(Personas **per); //Rutina para eliminar todos los envios de una persona
				void imprimirArrayEnteros(long int* const arrayInt, int nroElementosArrayInt);
				void swap(long int* a, long int* b); //Rutina swap utilizada por el ordenamiento burbuja
				void BurbujaEnteros(long int* const arrayInt, int nroElementosInt); //Metodo de ordenamiento burbuja

				  /////Personas//////

				Personas *buscarpersona(Personas *per, long int cedula, char nombre[]); //Funcion para buscar una persona mediante cedula o nombre
				void mostrartodo(Personas *per);            //Rutina para mostrar todas las personas
				void modificarpersona (Personas **per);		//Rutina para modificar persona
				void mostrardatospersona(Personas *per); //Rutina para mostrar datos de una sola persona
				void Eliminarpersona(Personas **per, int cedula); //Rutina para eliminar persona
				void agregarpersona(Personas **per); //Rutina para agregar una persona
				void guardarper(Personas *per); //Rutina para guardar en archivos la lista dinamica de  personas
				void cargarper(Personas **per); //Rutina para llenar la lista de personas con el archivo de personas

					/////Empresas/////

				Empresas *buscarempresa(Empresas *emp, int codigo, char nombre[], int tipo); //Funcion para buscar una empresa mediante codigo, nombre o tipo
 				void mostrartodoemp(Empresas *emp, int tipo);  //Rutina para mostrar todas las empresas
				void ingtipo(int *tipo);	//Rutina para llenar el tipo de una empresa
				void ingtel(char *tlf);    //Rutina para ingresar el numero de telefono
				void ingcodigo(int *codigo); //Rutina para ingresar el codigo
				void agregarempresa(Empresas **emp); //Rutina para agregar empresa
				void modificarempresa(Empresas **emp); //Rutina para modificar empresa
				void mostrardatosempresa(Empresas *emp); //Rutina para mostrar datos de una sola empresa
				void Eliminarempresa(Empresas **emp,int codigo, Personas **per); //Rutina para eliminar empresa
				void guardaremp(Empresas *emp); //Rutina para guardar la lista de  empresas en archivos
				void cargaremp(Empresas **emp); //Rutina para llenar la lista de empresas con el archivo de empresas

					/////Productos//////

				Productos *buscarproductos(Empresas *emp, int codigo);	//Funcion para buscar un producto mediante codigo
				Productos *buscarproductosenempresa(Empresas *emp, int codigo); //Funcion para buscar un producto (en una unica empresa) mediante codigo
				void agregarproducto(Productos **prod, Empresas **emp, int codigo); //Rutina para agregar un producto
				void mostrardatosprod(Productos *prod);	 //Rutina para mostrar los datos de un producto
				void modificarproducto (Productos *prod); //Rutina modificar un producto
				void Eliminarproducto(Empresas **emp, int codigo, Personas **per); //Rutina para eliminar un producto

					/////Envios/////

				Prodinc *buscarprodinc(Prodinc *prodinc, int codigo); //Funcion para buscar un producto incluido
				float PrecioTotal (Prodinc *prodinc);	//Funcion para hallar el precio total de un pedido
				bool existeenvio(Personas *per, int codigo); //Funcion para saber si un envio exite o no
				Pedidos *buscarenvios(Personas *per, int factura); //Funcion para buscar un pedido mediante una factura
				void eliminarprodinc (Pedidos **ped, int codigo); //Rutina para eliminar un producto incluido
				void agregarproductoincluido (Prodinc **prodinc, Empresas *emp); //Rutina para agregar un producto incluido
			 	void agregarenvio(Personas **per, Empresas *emp); //Rutina para agregar un envio
				void mostrarfactura (Personas *per, int factura); //Rutina para mostrar una factura
				void cerrarenvio (Personas **per, int copiafactura); //Rutina para cerrar un envio
				void mostrarproductosincluidos (Prodinc *prodinc); //Rutina para mostrar productos incluidos
				void Modificarenvio (Personas **per, int copiafactura, Empresas *emp); //Rutina para modificar un envio
				void eliminarenvio(Personas **per, int factura); //Rutina para eliminar un envio
				void eliminarenvioaux(Personas **per); //Rutina auxiliar para eliminar un envio, validandose codigo de la empresa, cedula del cliente y numero de factura para eliminar

					/////Consultas y extras //////

				void Datosemp(int codigo, Personas *per, int *entt, int *noentt, int *clientest, float *ingtotalt, float *promgastadot, int *clientesverift);
				int totalventas(Personas *per,int codigo); //Funcion que devuelve la cantidad de ventas de una empresa en especifico
				float totaling(Personas *per,int codigo, int i); //Funcion que devuelve el ingreso total entregado o no entregado de una empresa
				float promedioproducto(Personas *per,int codigo); //Funcion para conocer el promedio de cantidad de productos por factura
				void infodeunaemp(Empresas *emp, Personas *per); //Rutina que dada una empresa muestra informacion de ella y sus clientes
				void mejorclientetotal(Personas *per);	//Rutina que muestra el mejor cliente por cantidad total percibida
				void mejorclienteproductos (Personas *per); //Rutina que muestra el mejor cliente por cantidad de productos comprados
				void peorclientetotal(Personas *per); //Rutina que muestra el peor cliente por cantidad total NO percibida
				void peorclienteproductos (Personas *per); //Rutina que muestra el peor cliente por cantidad total de productos NO comprados
				void infocliente(Personas *per); //Rutina que dado la cedula de una persona, muestra los detalles de cada pedido realizado
				int contarprod(Personas *per, int codigoPrt, int codigoEmp, int opcion); //Funcion que cuenta la cantidad pedida (Entregada o no dependiendo de su opcion) de un producto en especifico
				void mejoresprod(Empresas *emp, Personas *per); //Rutina que muestra los mejores productos (mas vendido y mejor ingreso)
				void peoresprod(Empresas *emp, Personas *per); //Rutina que muestra los peores productos (menos vendido y peor ingreso)
				void infodeunaper(Personas *per, Empresas *emp);/*Rutina que dada una persona muestra el total de: pedidos hechos, productos adquiridos, monto pagado por los productos. Luego
				se muestran la(s) empresa(s) con el total de facturas, las cantidades de productos y monto de cdaa uno*/
				void infopersona_empresa (Personas *per, Empresas *emp);//Rutina que muestra informacion de una persona relacionada a una empresa
				void infopersona_empresadetallada(Personas *per, Empresas *emp);//Rutina que muestra la informacion de una personas (y sus pedidos) en relacion a una empresa, de forma detallada
				Pedidos *montomasalto(Pedidos *auxped); //Rutina que devuleve la direccion de memoria, donde se encuentra el pedido con el monto mas alto
				void mostrarfacturasentregadas(Personas *per,Pedidos **auxped,Empresas *emp); //Rutina para mostrar los numeros de las facturas entregadas y ordenarlo por monto total o por fecha de emision
				void borrarLista(Pedidos **l); //Rutina para borrar una lista
				Pedidos *fechamasreciente(Pedidos *auxped); //Rutina que devuelve la direccion de memoria, donde se encuentra el pedido con la fecha mas reciente
				Personas *personacantidadmasalta(Personas *tper,int *mayor,int *menor); //Rutina para buscar la persona con la mayor cantidad de productos comprada
				Personas *personamontomasalto(Personas *tper,float *mayor,float *menor); //Rutina para buscar la persona con el mayor monto total de compras realizadas (todos los pedidos entregados)
				void mayorpormonto(Personas **auxper, int a); //Rutina para mostrar las personas con mayor monto gastado 
				void mayorporcantidad(Personas **auxper, int a); //Rutina para mostrar las personas con la mayor cantidad de productos comprados
				void mayoresconsultas(Personas *per, int x); //Rutina para mostrar las personas con mayores montos de compras realizadas y mayor cantidad de productos comprados
				Empresas *empresamayor(int array[],float *ingreso,int a,Personas *per,Empresas *emp); //Funcion que devuelve la empresa con mayor ingreso logrado
                int cantidad ( Personas *per, int codigo ,int z);//Funcion que devuelve la cantidad de productos en facturas entregadas o no entregadas de una empresa en especifico
                void mayoresempresas(Empresas *emp,Personas *per,int z); //Rutina auxiliar para mostrar las empresas con mayores ingresos logrados (4.3.1) y las empresas con mayor cantidad de productos vendidos (4.3.2)
                Empresas *empresacantidad(int array[],int y,Personas *per,Empresas *emp,int *cantidadv); //Funcion que devuelve la empresa con mayor cantidad de productos vendidos

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					int main() {   //   Inicio del programa

					Encabezado ();
					printf("\n\n");
					system("pause");
					system (" cls ");

					system (" color 0F ");
					printf (" \n ");

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					/*******************************
					 *   Declaracion de variables  *
					 ******************************/

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						/***************************************
						 *   Registros, Punteros y/o Vectores  *
						 **************************************/

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//   Variables

					char copianombre[21],copianombreEmp[21],copiaop[2],copiaaux[2],copiaaux2[2], copiaopcon[2], copiaconsulta[2],copiaopmod[2],copiaopemtipo[2],copiaactivo[2],copiaopemtipo1[2];
					int titulo = 0;
					int op, aux, aux2, opcon, consulta, opmod, copiape;
					int tanio, tmes, tdia, tcedula;
					char tciu[16], tdir[41], tnombre[21];
					int activo, copiacodigo,copiatipo,x;
					long int copiacedula,valn;
					int copiafactura;
					int copiaempresa, copiaproducto;

						Productos *prod=NULL, productos;
						Empresas *emp=NULL, empresas;
						Personas *per=NULL, personas;
						Pedidos *ped=NULL, pedidos;
						Pedidos *auxped=NULL; //Lista auxiliar para consultas
						Prodinc *prodinc=NULL, prodInc;

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				cargarper(&per);
				cargaremp(&emp);

					do {

						if (titulo==0){
							printf("  Bienvenidos a YUMMY!!!\n\n");
							titulo++;
						} else	printf("\t YUMMY \n\n");

						printf("\t MENU\n\n");

						printf(" 1- Personas\n 2- Empresas y Productos\n 3- Ordenes\n 4- Consultas\n\n 0- Salir\n\n ");

						fflush(stdin);
						introduciropcion(&op);

						system("cls");
						switch (op) {

							//Personas
								case 1:
									do {
										printf("\n\tPersonas\n\n");
										printf(" 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- Volver\n\n ");
										fflush(stdin);
										introduciropcion(&aux);
										system("cls");

										switch (aux)
										{
											case 0:
											break;
											//Agregar Persona
											case 1: printf("\n\tAgregar\n\n");
													agregarpersona(&per);
													system("cls");
													printf("\n\n\tPersona agregada con exito!!!\n\n");
											break;
											//Modificar Persona
											case 2 : printf("\n\tModificar\n\n");
													if (per)
														modificarpersona(&per);
													else  printf(" No existe ninguna persona en el Sistema\n\n");
											break;
											//Consultar Persona
											case 3: printf("\n\tConsultar\n\n");
													copiacedula=0;
													if (per) {
														printf(" Mediante que opcion desea consultar?\n");
														printf(" 1- Cedula\n 2- Nombre y Apellido \n");

														do {
															fflush(stdin);
															introduciropcion(&consulta);
														} while(consulta!=1 && consulta!=2);
														system("cls");
														switch (consulta)
														{
														//Cedula
														case 1: printf("\n\n Ingrese el numero de cedula de la persona: ");
																ingnum(&copiacedula);
																printf("\n\n");
														break;
														//Nombre y Apellido
														case 2:
																printf("\n\n Ingrese el nombre y apellido del usuario a consultar: ");
																ingnombre(copianombre);
														break;
														}
												mostrardatospersona(buscarpersona(per, copiacedula, copianombre));
												/*Para consultar, en caso buscarpersona es una funcion que nos devolvera
												un apuntador de donde esta la persona que se desea consultar, ese apuntador lo recibe
												la funcion mostrardatospersona que imprimira por pantalla los datos de la persona*/
													} else printf(" No existe ninguna persona en el Sistema\n\n");

											break;
											//Eliminar Persona
											case 4: printf("\n\tEliminar\n\n");
													if (per)
													 {
														printf(" Ingrese la Cedula de la Persona a Eliminar: ");
														ingnum(&copiacedula);
															if (buscarpersona(per, copiacedula, vacio))
															{
																Eliminarpersona(&per, copiacedula);
																system("cls");
								 								printf("\n\tPersona eliminada con exito!!!\n\n");
															} else
															{
																printf("\n No existe ninguna persona con el numero de cedula ingresado\n\n");
															}
													} else printf(" No existe ninguna persona en el sistema\n\n");
											break;
											default:
													printf(" Debe elegir una opcion valida\n");
										}    // Fin del 1er Switch
										if (aux !=0)
										{
											system("pause");
		    								system("cls");
										}

										}

								while(aux !=0);

								break;

				/////////////////////////////////////////////////////////////////////////////////

							//Empresas y Productos
								case 2 :
									do {
										printf("\n\tEmpresas y Productos\n\n");
										printf(" 1- Empresas\n 2- Productos\n\n 0- Volver\n\n ");
										fflush(stdin);
										introduciropcion(&aux);
										system("cls");

										switch (aux) {
											case 0:
											break;
											//Empresas 2.1
											case 1:
													do {
														printf("\n\tEmpresas \n\n");
														printf(" 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- Volver\n\n ");
														fflush(stdin);
														introduciropcion(&aux2);
														system("cls");

														switch (aux2) {
															case 0:
															break;
															//Agregar Empresa
															case 1:
																	printf("\n\tAgregar\n\n");
																	agregarempresa(&emp);
																	fflush(stdin);
																	system("cls");
																	printf("\n\n\tEmpresa agregada con exito!!!\n\n");
															break;
															//Modificar Empresa
															case 2:
																	printf("\n\tModificar\n\n");
																	if (emp)
																	   	modificarempresa(&emp);
																	else  printf(" No existe ninguna empresa en el sistema\n\n");
															break;
															//Consultar Empresa
															case 3:
																	printf("\n\tConsultar\n\n");
																	copiacodigo=0;

																	if (emp)
																	{
																		printf(" Mediante que opcion desea consultar?\n");
																		printf(" 1- Codigo\n 2- Nombre de la Empresa \n ");

																	do {
																		fflush(stdin);
																		introduciropcion(&consulta);
																		if (consulta!=1 && consulta!=2) {
																			printf("\n\n Debe ingresar una de las opciones indicadas \n ");

																		}
																	} while(consulta!=1 && consulta!=2);
																		system("cls");
																	switch (consulta)
																	{
																		//Codigo
																	    case 1:
																				printf("\n\n Ingrese el Codigo de la Empresa: ");
																				ingcodigo(&copiacodigo);
																		break;
																		//Nombre de la empresa
																		case 2:
																				printf("\n\n Ingrese el Nombre de la Empresa: ");
																				ingnombre(copianombre);
																		break;
																	}
																mostrardatosempresa(buscarempresa(emp,copiacodigo,copianombre, 0));
																/*Para consultar, en caso buscarempresa es una funcion que nos devolvera
																un apuntador de donde esta la empresa que se desea consulta, ese apuntador lo recibe
																la funcion mostrardatosempresa que imprimira por pantalla los datos de la empresa*/
																	} else
																			{
																			printf(" No existe ninguna empresa en el sistema\n\n");
																			}

															break; //Consultar

															//Eliminar Empresa
															case 4:
																printf("\n\tEliminar\n\n");
																if (emp)
																{
																	printf(" Ingrese el codigo de la empresa a eliminar: ");
																	ingcodigo(&copiaempresa);
																	Eliminarempresa(&emp,copiaempresa, &per);
																}
																else {
																	printf("No existen ninguna empresa en el sistema \n\n");
																}
															break;

														default:printf(" Debe elegir una opcion valida");
																sleep(2);
														}
														if (aux2 !=0)
														{
														system("pause");
														system("cls");
														}

														} while (aux2 !=0);

								break; //empresas

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								//Productos 2.2
								case 2:
										if (emp==NULL)
										{
											printf("\n No existe ninguna empresa en el sistema\n\n");
											system("pause");
											break;
										}

										do{
											printf("\n\tProductos \n\n");
											printf(" 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar Productos\n\n 0- Volver\n\n ");
											fflush(stdin);
											introduciropcion(&aux2);
											system("cls");
											switch (aux2)
											{
												case 0:
												break;
												//Agregar Producto
												case 1:
														fflush(stdin);
														printf("\n\tAgregar\n\n");
														int codigocopia;
														printf(" A que empresa pertenece este producto? (ingrese su codigo): ");
														ingcodigo(&codigocopia);
														printf("\n");
														if (buscarempresa(emp, codigocopia, copianombre, 0)==NULL) {
															 printf(" La empresa no se encuentra en el sistema\n\n");
														} else { agregarproducto(&prod, &emp, codigocopia); }
												break;
												//Modificar Producto
												case 2:
														printf("\n\tModificar\n\n");
														Empresas *temp1;
														Productos *prod1;
														printf(" A que empresa pertenece este producto? (ingrese su codigo): ");
														ingcodigo(&codigocopia);
														printf("\n");
														temp1=buscarempresa(emp,codigocopia,copianombre,0);
															if (temp1)
															{
																printf(" EMPRESA: %s\n\n", temp1->nombreEmp);
																printf(" Introduzca el Codigo del Producto a Modificar: ");
																ingcodigo(&copiacodigo);
																prod1=buscarproductosenempresa(temp1,copiacodigo);
																modificarproducto(prod1);
															}
															else{printf(" La empresa no se encuentra en el sistema\n\n");}
												break;

												//Consultar Producto
												case 3:
														printf("\n\tConsultar\n\n");
														Empresas *temp2;
														Productos *prod2;
														printf(" A que empresa pertenece el producto a consultar? (ingrese su codigo): ");
														ingcodigo(&codigocopia);
														printf("\n");
														temp2=buscarempresa(emp,codigocopia,copianombre,0);
														if (temp2)
														{
															printf(" EMPRESA: %s\n\n", temp2->nombreEmp);
															printf(" Introduzca el Codigo del Producto a consultar: ");
															ingcodigo(&copiacodigo);
															prod2=buscarproductosenempresa(temp2,copiacodigo);
															mostrardatosprod(prod2);
														}
														else{printf(" La empresa no se encuentra en el sistema\n\n");}
												break;

												//Eliminar Producto
												case 4:
														printf("\n\tEliminar Productos\n\n");
														Empresas *temp;
														Productos *prod;
														printf(" A que empresa pertenece el producto a eliminar? (ingrese su codigo): ");
														ingcodigo(&codigocopia);
														printf("\n");
														temp=buscarempresa(emp,codigocopia,copianombre,0);
														if (temp)
														{
															printf(" EMPRESA: %s\n\n", temp->nombreEmp);
															printf(" Introduzca el Codigo del Producto a eliminar: ");
															ingcodigo(&copiacodigo);
															prod=buscarproductosenempresa(temp,copiacodigo);
															if(prod){
																Eliminarproducto(&temp,copiacodigo, &per);
															} else {printf("\n El producto no se encuentra en el sistema\n");}
														}
														else{printf(" La empresa no se encuentra en el sistema\n\n");}
												break;

											default: printf(" Debe elegir una opcion valida ");
													sleep(2);
											}

												if (aux2 !=0)
													{
													system("pause");
													system("cls");
													}

											}while(aux2!=0);
												break;
												default: printf(" Debe elegir una opcion valida ");
												sleep(2);
											}
									system("cls");
										}
						while(aux!=0);

				/////////////////////////////////////////////////////////////////////////////////

						break;

				/////////////////////////////////////////////////////////////////////////////////

							//Ordenes de envio
							case 3:
								if ((per==NULL)||(emp==NULL))
								{
									printf("\n Primero se deben agregar Personas y/o Empresas\n\n");
									system("pause");
								break;
								}
								do {
									printf("\n\tOrdenes\n\n");
									printf(" 1- Solicitar Envio\n 2- Modificar Envio\n 3- Consultar Envio\n 4- Cierre de Envio\n 5- Eliminar un Envio\n\n 0- Volver\n\n ");
									fflush(stdin);
									introduciropcion(&aux);
									system("cls");
									switch (aux) {
										case 0:
										break;
										//Solicitar envio 3.1
										case 1:
												printf("\n\tSolicitar Envio \n\n");
												agregarenvio(&per, emp);
										break;
										//Modificar Envio 3.2
										case 2:
												printf("\n\tModificar Envio \n\n");
												printf(" Ingrese el numero de factura: ");
												ingcodigo(&copiafactura);
												if (buscarenvios(per, copiafactura)==NULL)
												{
													printf("\n El pedido con ese numero de factura no se encuentra en el sistema\n\n");
													system("pause");
													break;
												}
												system("cls");
												Modificarenvio (&per, copiafactura, emp);
										break;
										//Consultar Envio 3.3
										case 3:
												printf("\n\tConsultar Envio \n\n");
												printf(" Ingrese el numero de factura: ");
												ingcodigo(&copiafactura);
												if (buscarenvios(per, copiafactura)==NULL)
												{
													printf("\n El pedido con ese numero de factura no se encuentra en el sistema\n\n");
													system("pause");
													break;
												}
												system("cls");
												mostrarfactura(per, copiafactura);
										break;
										//Cierre de envio 3.4
										case 4:
												printf("\n\tCierre de envio \n\n");
												printf(" Ingrese el numero de factura: ");
												ingcodigo(&copiafactura);
												cerrarenvio (&per, copiafactura);
										break;
										//Eliminar un Envio 3.5
										case 5:
												printf("\n\tEliminar un Envio \n\n");
												eliminarenvioaux(&per);
										break;
										default: printf(" Debe elegir una opcion valida \n\n");
										}
										system("cls");
										}
										while(aux!=0);
							break;

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

							//Consultas
							case 4:
									do {
										printf("\n\tConsultas\n\n");
										printf(" 1- Empresas\n 2- Personas\n 3- Sistema\n\n 0- Volver\n\n ");
										fflush(stdin);
										introduciropcion(&aux);
										system("cls");
										switch (aux) {
											case 0:
											break;
											//Empresas 4.1
											case 1:
													if 	(!(existeenvio(per,0)))
													{
														printf("\n\tEmpresas\n\n");
														printf(" No existe ningun pedido en el sistema\n\n");
														system("pause");
														break;
													}
													do {
														printf("\n\tEmpresas\n\n");
														printf(" 1- Informacion de todas las Empresas\n 2- Informacion de una Empresa\n 3- Informacion de un Cliente\n 4- Mostrar Mejor/Peor Cliente\n 5- Mostrar Mejor/Peor Producto\n\n 0- Volver\n\n ");
														fflush(stdin);
														introduciropcion(&opcon);
														system("cls");
														switch (opcon) {
															case 0:
															break;
															//Info de todas las Empresas 4.1.1
															case 1:
																	printf("\n\tInformacion de todas las Empresas\n\n");
																	int ent, noent, clientes, clientesverif;
																	ent = 0; noent = 0; clientes = 0; clientesverif = 0;
																	float ingtotal, promgastado;
																	ingtotal = 0; promgastado = 0;
																	Empresas *temp;
																	temp = emp;
																	for ( ;temp;temp=temp->prox){
																		printf(" %s:  ", temp->nombreEmp);
																		Datosemp(temp->codigoEmp, per, &ent, &noent, &clientes, &ingtotal, &promgastado, &clientesverif);
																	}
																	if (clientesverif != 0)
																		promgastado = ingtotal/clientesverif;
																		printf("\n ------------------\n");
																		printf("TOTAL:  PEDIDOS ENTREGADOS: %i - PEDIDOS NO ENTREGADOS: %i - CLIENTES ATENDIDOS: %i - INGRESO TOTAL VENDIDO: %.2f$ - PROMEDIO DE GASTO POR CLIENTE: %.2f$ \n", ent, noent, clientes, ingtotal, promgastado);
																		printf(" ------------------\n\n");
																	system("pause");
															break;
															//Info de una Empresa 4.1.2
															case 2:
																	printf("\n\tInformacion de una Empresa \n\n");
																	copiacodigo=0;
																	printf(" Mediante que opcion desea consultar?\n");
																	printf(" 1- Codigo\n 2- Nombre de la Empresa \n ");
																	do {
																		fflush(stdin);
																		introduciropcion(&consulta);
																		if (consulta!=1 && consulta!=2) {
																			printf("\n\n Debe ingresar una de las opciones indicadas \n ");

																		}
																	} while(consulta!=1 && consulta!=2);
																	system("cls");
																	switch (consulta){
																		//Codigo
																		case 1:
																				printf("\n\n Ingrese el Codigo de la Empresa: ");
																				ingcodigo(&copiacodigo);
																		break;
																		//Nombre de la empresa
																		case 2:
																				printf("\n\n Ingrese el Nombre de la Empresa: ");
																				ingnombre(copianombre);
																		break;
																	}
																	Empresas *pemp;
																	pemp = buscarempresa(emp,copiacodigo,copianombre, 0);
																	if (pemp){
																		if 	(!(existeenvio(per, pemp->codigoEmp))) {
																			printf(" No existe ningun pedido hacia esta empresa en el sistema\n\n");
																			system("pause");
																			break;
																		}
																		infodeunaemp(pemp, per);
																	} else {printf("\n La empresa no se encuentra en el sistema\n\n");}
																	system("pause");
															break;
															//Info de un Cliente 4.1.3
															case 3:
																	printf("\n\tInformacion de un Cliente\n\n");
																	infocliente(per);
																	printf("\n");
																	system("pause");
															break;
															system("pause");
															break;
															//Mostrar Mejor/Peor Cliente 4.1.4
															case 4:
																	printf("\n\tMostrar Mejor/Peor Cliente\n\n");
																	//Mejor cliente por cantidad total percibida
																	mejorclientetotal(per);
																	//Mejor cliente por cantidad de productos comprados
																	mejorclienteproductos (per);
																	//Peor cliente por cantidad total no percibida
																	 peorclientetotal(per);
																	//Peor cliente por cantidad de productos no comprados
																	peorclienteproductos (per);
																	system("pause");
															break;
															system("pause");
															break;
															//Mostrar Mejor/Peor Producto 4.1.5
															case 5:
																	printf("\n\tMostrar Mejor/Peor Producto\n\n");
																	mejoresprod(emp, per);
																	peoresprod(emp, per);
																	system("pause");
															break;
															default: printf(" Debe elegir una opcion valida \n");
																	sleep(2);
															}
															system("cls");
															} while(opcon!=0);
															break;
											//Personas 4.2
											case 2:
													do {
														printf("\n\tPersonas\n\n");
														printf(" 1- Informacion sobre una Persona\n 2- Informacion Persona/Empresa\n\n 0- Volver\n\n ");
														fflush(stdin);
														introduciropcion(&opcon);
														system("cls");
														switch (opcon) {
															case 0:
															break;
															//Info sobre una Persona 4.2.1
															case 1:
																	copiacedula=0;
																	printf("\n\tInformacion sobre una Persona\n\n");
																	printf(" Mediante que opcion desea consultar?\n");
																	printf(" 1- Cedula\n 2- Nombre y Apellido \n ");
																	do {
																		fflush(stdin);
																		introduciropcion(&consulta);
																		if (consulta!=1 && consulta!=2) {
																			printf("\n\n Debe ingresar una de las opciones indicadas \n ");

																		}
																	} while(consulta!=1 && consulta!=2);
																	system("cls");
																	switch (consulta){
																		//Cedula
																		case 1:
																				printf("\n\n Ingrese el numero de cedula de la persona: ");
																				ingnum(&copiacedula);
																		break;
																		//Nombre
																		case 2:
																				printf("\n\n Ingrese el Nombre y apellido del usuario a consultar: ");
																				ingnombre(copianombre);
																		break;
																	}
																	if (buscarpersona(per, copiacedula, copianombre)){
																		infodeunaper(buscarpersona(per, copiacedula, copianombre), emp);
																	} else {
																			printf("\n La persona no se encuentra en el sistema\n\n");
																			}
																	system("pause");
															break;
															// Info Persona/Empresa 4.2.2
															case 2:
																copiacedula=0;
																copiacodigo=0;
																char copianombre2[21];
																printf("\n\tInformacion Persona/Empresa \n\n");
																printf(" Persona: \n\n");
																//Persona
																printf(" Mediante que opcion desea consultar?\n");
																printf(" 1- Cedula\n 2- Nombre y Apellido \n ");
																do {
																	fflush(stdin);
																	introduciropcion(&consulta);
																	if (consulta!=1 && consulta!=2) {
																		printf("\n\n Debe ingresar una de las opciones indicadas \n ");

																	}
																} while(consulta!=1 && consulta!=2);
																system("cls");
																switch (consulta){
																	//Cedula
																	case 1:
																			printf("\n\n Ingrese el numero de cedula de la persona: ");
																			ingnum(&copiacedula);
																	break;
																	//Nombre
																	case 2:
																			printf("\n\n Ingrese el Nombre y apellido del usuario a consultar: ");
																			ingnombre(copianombre);
																	break;
																}
																system("cls");
																printf("\n\tInformacion Persona/Empresa \n\n");
																printf(" Empresa: \n\n");
																//empresa
																printf(" Mediante que opcion desea consultar?\n");
																printf(" 1- Codigo\n 2- Nombre de la Empresa \n ");
																do {
																	fflush(stdin);
																	introduciropcion(&consulta);
																	if (consulta!=1 && consulta!=2) {
																		printf("\n\n Debe ingresar una de las opciones indicadas \n ");

																	}
																} while(consulta!=1 && consulta!=2);
																system("cls");
																switch (consulta){
																	//Codigo
																	case 1:
																			printf("\n\n Ingrese el Codigo de la Empresa: ");
																			ingcodigo(&copiacodigo);
																	break;
																	//Nombre de la empresa
																	case 2:
																			printf("\n\n Ingrese el Nombre de la Empresa: ");
																			ingnombre(copianombre2);
																	break;
																}
																if ((!buscarpersona(per, copiacedula, copianombre)) || (!buscarempresa(emp, copiacodigo, copianombre2, 0))) {
																	printf("\n La persona y/o Empresa no se encuentra en el sistema\n\n");
																	system("pause");
																	break;
																}
																infopersona_empresadetallada(buscarpersona(per, copiacedula, copianombre), buscarempresa(emp, copiacodigo, copianombre2, 0));
																system("pause");
															break;
															default: printf("  Debe elegir una opcion valida \n");
																	sleep(2);
															}
														   system("cls");
															} while(opcon!=0);
											break;
											//Sistema 4.3
											case 3:
													do {
														printf("\n\tSistema\n\n");
														printf(" 1- Mostrar las Empresas con los mayores ingresos logrados\n 2- Mostrar las Empresas con la mayor cantidad de productos vendidos\n 3- Mostrar las personas con los mayores montos de compras realizadas\n 4- Mostrar las personas con mayor cantidad de productos comprados\n 5- Mostrar numero facturas entregadas\n\n 0- Volver\n\n ");
														fflush(stdin);
														introduciropcion(&opcon);
														system("cls");
														switch (opcon) {
															case 0:
															break;
															//Mostrar las Empresas con los mayores ingresos logrados 4.3.1
															case 1:
																	printf("\n\tMostrar las Empresas con los mayores ingresos logrados\n\n");
																	mayoresempresas(emp,per,1);
																	system("pause");
															break;

															//Mostrar las Empresas con la mayor cantidad de productos vendidos 4.3.2
															case 2:
																	printf("\n\tMostrar las Empresas con la mayor cantidad de productos vendidos\n\n");
																	mayoresempresas(emp,per,2);
																	system("pause");
															break;

															//Mostrar las personas con los mayores montos de compras realizadas 4.3.3
															case 3:
																	printf("\n\tMostrar las personas con los mayores montos de compras realizadas\n\n");
																	printf("\n PERSONAS CON MAYORES MONTOS DE COMPRAS REALIZADAS \n\n");
																	mayoresconsultas(per,1);
																	system("pause");
															break;


															//Mostrar las personas con mayor cantidad de productos comprados 4.3.4
															case 4:
																	printf("\n\tMostrar las personas con mayor cantidad de productos comprados\n\n");
																	printf("\n PERSONAS CON MAYOR CANTIDAD DE PRODUCTOS COMPRADOS \n\n");
																	 mayoresconsultas(per, 2);
																	system("pause");
															break;


															//Mostrar facturas entregadas 4.3.5 revisar cuando no hay facturas
															case 5:
																	
																	printf("\n\tMostrar facturas entregadas \n\n");
																	if(existeenvio(per, 0)){
																		mostrarfacturasentregadas(per,&auxped,emp);
																	}
																	else{
																		printf("\n No existe ninguna factura en el sistema \n");
																	}

																	system("pause");
																	system ("cls");
															break;
															default: printf(" Debe elegir una opcion valida \n");
																	 sleep(2);
															}
															system("cls");
															 } while(opcon!=0);
												break;
												default: printf(" Debe elegir una opcion valida\n");
														sleep(2);
														}
											system("cls");
										} while(aux!=0);
					  		  break;

				/////////////////////////////////////////////////////////////////////////////////
				default:
						if (op != 0)
						{
							printf(" Debe elegir una opcion valida ");
							sleep(2);
						}
					}
					system("cls");

				}
					while(op !=0);
				/////////////////////////////////////////////////////////////////////////////////

				guardarper(per);
				guardaremp(emp);

				printf("\n Hasta Pronto!!!\n");
				return 0;

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				}      //   Fin del programa

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					/*******************************
					 *   Declaracion de funciones
					 ******************************/

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				void Encabezado ()
					{
						system (" color 0A");
						printf (" \n ");
						printf ("\t  Universidad Catolica Andres Bello \n\t    Algoritmos y Programacion II \n\n\t     Maria Valentina Gonzalez \n \t \t    Arturo Hung \n\t \t   Italo Visconti\n\t \t   Rafael Zappala");
						printf("\n\n |Contamos con guardado automatico al finalizar el programa ;)|");
					}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*guardarper es una funcion que nos permite al final de cada programa, guardar en un archivo la lista de persona*/
				void guardarper(Personas *per){

					FILE *personas;
				  	personas = fopen ("personas.txt","w");

						if (personas == NULL){
						printf("\n Error! no se ha podido crear el archivo\n\n");
						system("pause");
						return;
						} else
							for ( ; per; per=per->prox){	//Personas
								fprintf(personas, "%li\n", per->cedula);
								fprintf(personas, "%s\n", per->nombre_apellido);
								fprintf(personas, "%i\n", per->fechas.anio);
								fprintf(personas, "%i\n", per->fechas.mes);
								fprintf(personas, "%i\n", per->fechas.dia);
								fprintf(personas, "%s\n", per->ciudad);
								fprintf(personas, "%s\n", per->direccion);

								Pedidos *ped;
								ped = per->aba;
									for ( ; ped; ped=ped->prox){	//Pedidos
										fprintf(personas, "%i\n", ped->codigoEmp);
										fprintf(personas, "%i\n", ped->entregados);
										fprintf(personas, "%i\n", ped->factura);
										fprintf(personas, "%i\n", ped->fechas.anio);
										fprintf(personas, "%i\n", ped->fechas.mes);
										fprintf(personas, "%i\n", ped->fechas.dia);
										fprintf(personas, "%f\n", ped->monto_total);
										Prodinc *prodinc;
										prodinc = ped->aba;
										for ( ; prodinc; prodinc=prodinc->prox){
											fprintf(personas, "%i\n", prodinc->codigoPrt);
											fprintf(personas, "%i\n", prodinc->cantidad);
											fprintf(personas, "%f\n", prodinc->precio);
										}
										fprintf(personas, "0\n");
									}
									fprintf(personas, "0\n");
							}
							fprintf(personas, "0\n");
					fclose(personas);
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*cargarper es una funcion que nos permite, al inicio de cada programa vaciar el archivo de personas en la lista de personas,*/
				void cargarper(Personas **per){
					Personas *tper = new Personas;
					Pedidos *ped, *tped;
					Prodinc *prodinc, *tprodinc;

					char x[1];
					long int nuloper;
					int nuloped, nuloprodinc;
					FILE *personas;

					if((personas=fopen("personas.txt", "r"))==NULL){
						printf("\n\t Es la primera vez entrando a yummy :) \n\n    [Esta a punto de descubrir el futuro en delivery] \n\n");
						system("pause"); system("cls");
					} else {
							fscanf(personas, " ", &x); 	//Para evitar un caso borde (.txt en blanco) leemos el primer "caracter" en este, para de esta manera NO entrar en el while y llegar al 'eof'
													   //de esta forma evitamos la impresion erronea del archivo en la lista
							fscanf(personas, "%li\n", &nuloper);
							while ((nuloper!=0)&&(!(feof(personas)))) {		//Personas
									tper->cedula = nuloper;
									fscanf(personas, " %[^\n]s\n", &tper->nombre_apellido);
									fscanf(personas, "%i\n", &tper->fechas.anio);
									fscanf(personas, "%i\n", &tper->fechas.mes);
									fscanf(personas, "%i\n", &tper->fechas.dia);
									fscanf(personas, " %[^\n]s\n", &tper->ciudad);
									fscanf(personas, " %[^\n]s\n", &tper->direccion);
									tper->aba = NULL;
									ped = tper->aba;

									fscanf(personas, "%i\n", &nuloped);
										while (nuloped!=0){				//Pedidos
											tped = new Pedidos;
											tped->codigoEmp = nuloped;
											fscanf(personas, "%i\n", &tped->entregados);
											fscanf(personas, "%i\n", &tped->factura);
											fscanf(personas, "%i\n", &tped->fechas.anio);
											fscanf(personas, "%i\n", &tped->fechas.mes);
											fscanf(personas, "%i\n", &tped->fechas.dia);
											fscanf(personas, "%f\n", &tped->monto_total);

											tped->aba = NULL;
											prodinc = tped->aba;

											fscanf(personas, "%i\n", &nuloprodinc);
												while (nuloprodinc!=0){		//Productos Incluidos
													tprodinc = new Prodinc;
													tprodinc->codigoPrt = nuloprodinc;
													fscanf(personas, "%i\n", &tprodinc->cantidad);
													fscanf(personas, "%f\n", &tprodinc->precio);
													if (prodinc){
													tprodinc->prox = prodinc;
													} else {
													tprodinc->prox = NULL;
													}
													tped->aba = tprodinc;
													prodinc = tprodinc;

													fscanf(personas, "%i\n", &nuloprodinc);
												}

											if (ped){
											tped->prox = ped;
											} else {
											tped->prox = NULL;
											}
											tper->aba = tped;
											ped = tped;

										fscanf(personas, "%i\n", &nuloped);
										}

									if (*per){
									tper->prox = *per;
									} else {
									tper->prox = NULL;
									}
									*per=tper;

									fscanf(personas, "%i\n", &nuloper);
									if (nuloper!=0) tper=new Personas;
							}
					}
						fclose(personas);

				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /*guardaremp es una funcion que nos permite al final de cada programa, guardar en un archivo la lista de empresas*/
				void guardaremp(Empresas *emp){

					FILE *empresas;

					if ((empresas=fopen("empresas.txt", "w"))==NULL){
						printf("\n Error! no se ha podido crear el archivo\n\n");
						system("pause");
						return;
					}
					else
						for ( ; emp; emp=emp->prox){
							fprintf(empresas, "%i\n", emp->codigoEmp);
							fprintf(empresas, "%s\n", emp->nombreEmp);
							fprintf(empresas, "%i\n", emp->tipo);
							fprintf(empresas, "%s\n", emp->tlf);
							fprintf(empresas, "%s\n", emp->direccion);
								Productos *prod;
								prod = emp->aba;
								for ( ; prod; prod=prod->prox){
									fprintf(empresas, "%i\n", prod->codigoPrt);
									fprintf(empresas, "%s\n", prod->descripcion);
									fprintf(empresas, "%i\n", prod->activo);
									fprintf(empresas, "%li\n", prod->precioUd);
								}
								fprintf(empresas, "0\n");

						}
					fprintf(empresas, "0");
					fclose(empresas);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*cargaremp es una funcion que nos permite, al inicio de cada programa vaciar el archivo de empresas en la lista de empresas*/
				void cargaremp(Empresas **emp){

					Empresas *temp = new Empresas;
					Productos *prod, *tprod;

					char x[1];
					int nuloemp, nuloprod;
					FILE *empresas;

					if((empresas=fopen("empresas.txt", "r"))==NULL){

					} else {
							fscanf(empresas, " ", &x); 	//Para evitar un caso borde (.txt en blanco) leemos el primer "caracter" en este, para de esta manera NO entrar en el while y llegar al 'eof'
													   //de esta forma evitamos la impresion erronea del archivo en la lista
							fscanf(empresas, "%i\n", &nuloemp);
							while ((nuloemp!=0)&&(!(feof(empresas)))) { //Empresas
									temp->codigoEmp = nuloemp;
									fscanf(empresas, " %[^\n]s\n", &temp->nombreEmp);
									fscanf(empresas, "%i\n", &temp->tipo);
									fscanf(empresas, "%s\n", &temp->tlf);
									fscanf(empresas, " %[^\n]s\n", &temp->direccion);

									temp->aba = NULL;
									prod = temp->aba;

									fscanf(empresas, "%i\n", &nuloprod);
										while (nuloprod!=0){		//Productos
											tprod = new Productos;
											tprod->codigoPrt = nuloprod;
											fscanf(empresas, " %[^\n]s\n", &tprod->descripcion);
											fscanf(empresas, "%i\n", &tprod->activo);
											fscanf(empresas, "%li\n", &tprod->precioUd);

											if (prod){
											tprod->prox = prod;
											} else {
											tprod->prox = NULL;
											}
											temp->aba = tprod;
											prod = tprod;

										fscanf(empresas, "%i\n", &nuloprod);
										}

									if (*emp){
									temp->prox = *emp;
									} else {
									temp->prox = NULL;
									}
									*emp=temp;

									fscanf(empresas, "%i\n", &nuloemp);
									if (nuloemp!=0) temp=new Empresas;
							}
					}
						fclose(empresas);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que convierte todas las letras de un string en mayusculas*/
					void  BloqMayus ( char s[] )	{
						int i;
						for (i = 0; s[i]!='\0'; i++)
						{
							if(s[i] >= 'a' && s[i] <= 'z')
								{
								s[i] = s[i] - 32;
								}
						}
					}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que nos permite validar dado un string, saber si tiene solo numeros o contiene letras*/
					int validar_num (char numero[])	{
							int i=0, sw=0,j;
							j=strlen(numero);
							while((i<j)&&(sw==0)){
								if(isdigit(numero[i])!=0){
									i++;
								}
								else
									{
										sw=1;
									}
							}
							return sw;
						}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que nos permite calcular el monto total de un pedido*/
					float PrecioTotal (Prodinc *prodinc) {
						float cont = 0;
							for ( ; prodinc; prodinc=prodinc->prox){
								cont += ((prodinc->precio)*(prodinc->cantidad));
							}
						return cont;
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para validar el ingreso de fechas, tanto que este en el rango (1900-2100) y no contenta letras*/
					void ingfecha(int *tanio, int *tmes, int *tdia) {
						char copia[5],copia1[3],copia2[3];
						int valn;

							do{
								printf("\n Anio: ");
								scanf("%s",&copia);
								valn=validar_num(copia);
								*tanio=atoi(copia);
								if ((valn!=0)||(*tanio<1900)||(*tanio>2100)) printf("\n El anio debe estar entre 1900 y 2100\n");
							}while((valn!=0)||(*tanio<1900)||(*tanio>2100));
							printf  (" \n");
							do{
								printf (" Mes: ");
								scanf ("%s",&copia1);
								valn=validar_num(copia1);
								*tmes=atoi(copia1);
								if ((valn!=0)||(*tmes<=0) || (*tmes>12)) printf("\n El mes debe estar entre 1 y 12\n\n");
							} while((valn!=0)||(*tmes<=0) || (*tmes>12));
							printf  (" \n");
							do{
								printf (" Dia: ");
								scanf ("%s",&copia2);
								valn=validar_num(copia2);
								*tdia=atoi(copia2);
								if ((valn!=0)||(*tdia<=0) || (*tdia>31)) printf("\n El dia debe estar entre 1 y 31\n\n");
							} while ((valn!=0)||(*tdia<=0) || (*tdia>31));
							printf  (" \n");
							fflush(stdin);

					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que el nombre no excede la cantidad de 20 caracteres*/
					void ingnombre(char *tnombre) {
						do{
							fflush(stdin);
							scanf (" %[^\n]s",&*tnombre);
							if (!(strlen(tnombre)<=20))
									printf(" La cadena debe ser menor a 20 caracteres: ");
						} while (!(strlen(tnombre)<=20));
						BloqMayus(tnombre);
						printf  (" \n");
						fflush(stdin);
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que la ciudad no excede la cantidad de 15 caracteres*/
					void ingciu(char *tciudad ) {
						do{
							fflush(stdin);
							scanf (" %[^\n]s",&*tciudad);
							if (!(strlen(tciudad)<=15))
								printf(" Debe ingresar un nombre menor a 15 caracteres: ");
						} while (!(strlen(tciudad)<=15));
						BloqMayus(tciudad);
						printf  (" \n");
						fflush(stdin);
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que la direccion no excede la cantidad de 40 caracteres*/
					 void ingdir(char *tdir) {
						do{
							fflush(stdin);
							scanf (" %[^\n]s",&*tdir);
							if (!(strlen(tdir)<=40))
								printf(" Debe ingresar una direccion menor a 40 caracteres: ");
						} while (!(strlen(tdir)<=40));
						BloqMayus(tdir);
						printf("\n\n");
						fflush(stdin);
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/* funcion para validar que la cedula introducida sea valida */
					void ingnum(long int *numero){
						char copia[10];
						int valn;

						do {

							scanf("%s",&copia);
							valn=validar_num(copia);
							*numero=atoi(copia);

							if((*numero==0)||(valn!=0)||(*numero>=maxlongint)){
								printf("\n Debe introducir un numero valido [ mayor a cero (0) ]: ");
							}
						}while ((*numero==0)||(valn!=0)||(*numero>=maxlongint));
						fflush(stdin);
						*numero=atoi(copia);

					 }

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				/*funcion para mostrar toda la lista de personas*/
		   			void mostrartodo(Personas *per){
					Personas *tper = per;
					for ( ; per; per=per->prox) {
							printf("--------------------------\n");
							printf(" NOMBRE Y APELLIDO: %s\n CEDULA: %i\n FECHA DE NAC: %i/%i/%i \n CIUDAD: %s\n DIRECCION: %s\n", per->nombre_apellido, per->cedula, per->fechas.dia, per->fechas.mes, per->fechas.anio, per->ciudad, per->direccion );
							printf("--------------------------\n");

						}
			  	}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para modificar persona*/
		  			void modificarpersona (Personas **per) {
					int valn, opmod, tanio, tmes, tdia;
					long int copiacedula;
					Personas *tper = *per;
					bool verif=false;
					printf(" Ingrese la Cedula de la Persona a Modificar: ");
					ingnum(&copiacedula);
					tper = buscarpersona(*per, copiacedula, tper->nombre_apellido);
					/*buscarpersona buscara en la lista *per, la cedula de persona
					que se desea modificar y delvolvera un apuntador en donde se encontro la persona,
					por lo tanto tper estara situado en el nodo de la persona que se desea modiciar*/
					if (tper) {
						mostrardatospersona(tper);
						system("pause");
					} else printf("\n La Cedula no se encuentra en el sistema\n");
						if (tper) {
							do {
								system("cls");
								printf("\n Que campo desea modificar?");
								printf("\n 1- Nombre y Apellido \n 2- Fecha de Nacimiento \n 3- Ciudad \n 4- Direccion \n\n 0- Volver \n\n");
								fflush(stdin);
								introduciropcion(&opmod);
								system("cls");
								switch (opmod) {
									case 0:
									break;
									//Modificar Nombre y Apellido
									case 1:
											printf("\n\n Introduzca su nuevo nombre y apellido: ");
											ingnombre(tper->nombre_apellido);
											printf  ("\n");
											fflush(stdin);
									break;
									//Modificar fecha de nacimiento
									case 2:
											printf ("\n\n Introduzca su nueva fecha de nacimiento: \n\n");
											ingfecha(&tper->fechas.anio, &tper->fechas.mes, &tper->fechas.dia);
											printf  (" \n");
											fflush(stdin);
									break;
									//Modificar Ciudad
									case 3:
											printf("\n\n Introduzca su nueva ciudad: ");
											ingciu(tper->ciudad);
											fflush(stdin);
									break;
									//Modificar Direccion
									case 4:
											printf("\n\n Introduzca su nueva direccion: ");
											ingdir(tper->direccion);
											fflush(stdin);
									break;
									default: printf(" Debe elegir una opcion valida\n");
											sleep(2);
									}
								} while (opmod!=0);
							}
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para validar que la opcion ingresada por el usuario es mayor que 1 y no contiene letras*/
					void introduciropcion(int *opcion) {
						char copia[2];
						int valn;
						fflush(stdin);
							do{
								printf("\n Introduzca numero de opcion -> ");
								scanf  ("%s",&copia);
								valn=validar_num(copia);
								if ((strlen(copia)>1)||(valn!=0))
									printf("\n Debe ingresar un numero \n ");
							} while ((strlen(copia)>1)||(valn!=0));
							*opcion=atoi(copia);
							fflush(stdin);
			   		}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion que buscara ya sea por cedula o nombre a una persona,en caso de que cedula==0, significa que la persona desea buscar
				por nombre, de lo contrario se busca por cedula*/
					Personas *buscarpersona(Personas *per, long int cedula, char nombre[]) {
						Personas *tper = per;
							for ( ; tper ; tper=tper->prox) {
								if (cedula == 0) {
									if (strcmp(tper->nombre_apellido, nombre)==0) return tper; //Se encontro usuario con el mismo nombre
								} else {if (tper->cedula == cedula)  return tper;	//Se encontro usuario con la misma cedula )
								   	}
					   }
						 return NULL;
					 }

			 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina que dada una persona muestra todos us datos*/
					void mostrardatospersona(Personas *per){

						 if (per==NULL) {
							 printf(" Persona no encontrada en el sistema \n");
						 	} else {
								 system("cls");
								 printf("\n Persona Encontrada en el Sistema \n");
								 printf("--------------------------------------------------------------------------\n");
								 printf (" Los datos de las personas son: ");
								 printf  (" \n \n");
								 printf (" \t NOMBRE Y APELLIDO: %s  \n",per->nombre_apellido);
								 printf (" \t CEDULA: %li \n",per->cedula);
								 printf (" \t FECHA DE NACIMIENTO: %d/%d/%d \n",per->fechas.dia,per->fechas.mes,per->fechas.anio);
								 printf (" \t CIUDAD: %s \n",per->ciudad);
								 printf (" \t DIRECCION: %s \n",per->direccion);
								 printf("--------------------------------------------------------------------------\n\n");
							}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para eliminar una persona, dada la lista y la cedula*/
					void Eliminarpersona(Personas **per, int cedula){
						if (*per){
							if ((*per)->cedula==cedula){
								if ((*per)->aba) {
								eliminartodoenvio(per);}
								struct personas *aux=(*per);
								(*per)=(*per)->prox;
								delete (aux);
							}
							else
							{
								Eliminarpersona(&(*per)->prox,cedula);
							}
						}
						else
							printf("\n No existe ninguna persona en el sistema \n\n");
					}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para agregar persona*/
					void agregarpersona(Personas **per) {
						Personas *tper;
						tper = new Personas;

						do {
							printf (" Introduzca su cedula: ");
							ingnum(&tper->cedula);
							fflush(stdin);
							if (buscarpersona(*per, tper->cedula, tper->nombre_apellido) != NULL) {//Se valida que la cedula sea unica
								printf("\n La cedula introducida ya se encuentra en el sistema ");
								printf("\n\n");
							}
						}	while (buscarpersona(*per, tper->cedula, tper->nombre_apellido) != NULL);

						printf (" Introduzca su nombre y apellido [20 caracteres]: ");
						ingnombre(tper->nombre_apellido);
						printf (" Introduzca su fecha de nacimiento:  \n");
						ingfecha(&tper->fechas.anio, &tper->fechas.mes, &tper->fechas.dia);
						printf (" Introduzca su ciudad [15 caracteres]: ");
						ingciu(tper->ciudad);
						printf (" Introduzca su direccion [40 caracteres]: ");
						ingdir(tper->direccion);
						tper->aba = NULL;
						printf(" %i -- %s -- %i/%i/%i -- %s -- %s\n", tper->cedula, tper->nombre_apellido, tper->fechas.dia, tper->fechas.mes, tper->fechas.anio, tper->ciudad, tper->direccion);
						system("pause");
						if (per==NULL) {
							*per = tper;
						 }
						else {
							tper->prox = *per;
							*per = tper;
						}

					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar el tipo de empresa*/
					void ingtipo(int *tipo){
					char *copiatipo;
					int valn;
					bool ver = false;
						do {
							fflush(stdin);
							scanf ("%s",&*copiatipo);
							valn=validar_num(copiatipo);
							if ((strlen(copiatipo)<1)||(valn!=0)) {
							}	else if ((atoi(copiatipo)>0) && (atoi(copiatipo)<4)){
							*tipo=atoi(copiatipo);
							ver = true;
							}
							if (ver==false)
								printf(" \n Opcion invalida, ingrese de nuevo -> ");
						} while (ver == false);
						fflush(stdin);
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que el numero de telefono sea solo numeros y no exceda los 12 caracteres*/
					void ingtel(char *tlf) {
						int valn;
							do {
								fflush(stdin);
								scanf  ("%s",&*tlf);
								valn=validar_num(tlf);
								if ((strlen(tlf)>12)||(valn!=0))
									printf(" Debe ingresar un numero de telefono adecuado [ 1 - 12 digitos ]: ");
							} while ((strlen(tlf)>12)||(valn!=0));
							fflush(stdin);
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para validar el codigo, que no poseea letras y no exceda la cantidad de digitos de un numero entero*/
				  	void ingcodigo(int *codigo){
				  		char copia[5];
						int valn;
							do{
								scanf("%s",&copia);
								valn=validar_num(copia);
								*codigo=atoi(copia);
								if((*codigo>=10000)||(*codigo==0)||(valn!=0)){
									printf("\n Debe ingresar un numero de 1 a 4 digitos: ");
								}
							}while ((*codigo>=10000)||(*codigo==0)||(valn!=0));
							fflush(stdin);
							*codigo=atoi(copia);
				   }
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion que buscara ya sea por codigo, nombre o tipo a una empresa,en caso de que codigo==0 y tipo==0, significa que la persona desea buscar
				por nombre, si codigo!=0 buscara por codigo y si tipo!=0 buscara por tipo */
					Empresas *buscarempresa(Empresas *emp, int codigo, char nombre[], int tipo) {
						Empresas *temp = emp;
						for ( ; temp ; temp=temp->prox) {
							if ((codigo == 0) && (tipo == 0)) {
								if (strcmp(temp->nombreEmp, nombre)==0) return temp; //Se encontro una empresa con el mismo nombre
							} else if (tipo == 0){
								if (temp->codigoEmp == codigo)  return temp;	//Se encontro una empresa con el mismo codigo
							} else if (codigo == 0){
							if (temp->tipo == tipo)  return temp;	//Se encontro una empresa con el mismo tipo
							} //Buscar por tipo nos ayudara a saber si existe por lo menos una empresa de ese tipo
					      }
					      return NULL;
				  }

				 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para agregar empresa*/
					void agregarempresa(Empresas **emp) {
						Empresas *temp;
						temp = new Empresas;
						fflush(stdin);

							do{
								printf(" Introduzca el codigo de la empresa [4 digitos]: ");
								ingcodigo(&temp->codigoEmp);
								if (buscarempresa(*emp, temp->codigoEmp, temp->nombreEmp, 0) != NULL) {//Se valida que el codigo de la empresa sea unico
									printf("\n El codigo introducido ya se encuentra en el sistema \n");
									sleep(1); printf("\n\n");
								}
							}	while (buscarempresa(*emp, temp->codigoEmp, temp->nombreEmp, 0) != NULL);
							printf("\n");
							printf (" Introduzca el nombre de la empresa [20 caracteres]: ");
							ingnombre(temp->nombreEmp);
							printf (" Introduzca el tipo de la empresa: \n");
							printf(" 1- Comidas\n 2- Alimentos\n 3- General \n ->");
							ingtipo(&temp->tipo);
							printf("\n");
							printf (" Introduzca el telefono de la empresa [12 caracteres]: ");
							ingtel(temp->tlf);
							printf("\n");
							printf (" Introduzca la direccion de la empresa [40 caracteres]: ");
							ingdir(temp->direccion);
							temp->aba = NULL;
							printf(" %i -- %s -- %i -- %s -- %s\n\n", temp->codigoEmp , temp->nombreEmp, temp->tipo, temp->tlf, temp->direccion);
							system("pause");
							if (emp==NULL) {
								*emp = temp;
							 }
							else {
								temp->prox = *emp;
								*emp = temp;
							}
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					void mostrartodoemp(Empresas *emp, int tipo){
						Empresas *temp = emp;
						for ( ; emp; emp=emp->prox) {
							if ((tipo==emp->tipo) || (tipo==4)){
								printf("--------------------------\n");
								printf(" CODIGO: %i\n NOMBRE: %s\n TIPO: %i\n TELEFONO: %s\n DIRECCION: %s\n", emp->codigoEmp, emp->nombreEmp, emp->tipo, emp->tlf, emp->direccion);
								printf("--------------------------\n");
							}
						}
					}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para modificar empresa*/
					void modificarempresa(Empresas **emp){

						Empresas *temp=*emp;
						int opmod,copiaempresa,copiaemtipo;
						char tnombre[20],tdir[40];

						printf(" Introduzca el Codigo de la Empresa a Modificar: ");
						ingcodigo(&copiaempresa);

						temp=buscarempresa(*emp,copiaempresa,temp->nombreEmp, 0);
						/*buscarempresa buscara en la lista *emp, el codigo de la empresa
						que se desea modificar y delvolvera un apuntador en donde se encontro la empresa,
						por lo tanto temp estara situado en el nodo de la empresa que se desea modiciar*/

						if (temp){
							mostrardatosempresa(temp);
							system("pause");
						}
						else {
							printf("\n El codigo no se encuentra en el sistema");
						}

						if (temp){
								do {
									system("cls");
									printf("\n Que campo desea modificar?");
									printf("\n 1- Nombre  \n 2- Tipo \n 3- Telefono \n 4- Direccion \n\n 0- Volver \n\n");
									fflush(stdin);
									introduciropcion(&opmod);
									system("cls");

								switch (opmod) {
									case 0:
									break;
									//Modificar Nombre empresa
									case 1:
											printf("\n\n Introduzca el nuevo nombre de la empresa: ");
											ingnombre(temp->nombreEmp);
											printf  ("\n");
											fflush(stdin);
									break;
									//Modificar tipo de empresa
									case 2:
										printf (" Introduzca el nuevo tipo de la empresa: \n");
										printf(" 1- Comidas\n 2- Alimentos\n 3- General \n ->");
										ingtipo(&temp->tipo);
										printf  ("\n");
										fflush(stdin);
									break;
									//Modificar telefono empresa
									case 3:
											printf (" Introduzca el nuevo telefono de la empresa [12 caracteres]: ");
											ingtel(temp->tlf);
											printf("\n");
									break;
									//Modificar Direccion empresa
									case 4:
										printf (" Introduzca la nueva direccion de la empresa [40 caracteres]: ");
										ingdir(temp->direccion);
									break;
									default: printf("Debe ingresar una opcion valida ");
											sleep(2);
							}

					} while(opmod!=0);

				  }
			 }

				/////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dada una empresa, muestra todos sus datos*/
				void mostrardatosempresa(Empresas *emp){

					if (emp==NULL){
						printf("\n Empresa no encontrada en el sistema \n");
					}
					else
					{
						printf("\n Empresa Encontrada en el Sistema \n\n");
						printf("--------------------------------------------------------------------------");
						printf ("\n Los datos de la empresa son: ");
						printf  (" \n\n");

						if (emp->codigoEmp<10) printf (" \t CODIGO DE LA EMPRESA: 000%i  \n",emp->codigoEmp);
						 else if (emp->codigoEmp<100) printf(" \t CODIGO DE LA EMPRESA: 00%i  \n",emp->codigoEmp);
					   	  else if (emp->codigoEmp<1000) printf(" \t CODIGO DE LA EMPRESA: 0%i  \n",emp->codigoEmp);
					    	else printf (" \t CODIGO DE LA EMPRESA: %i  \n",emp->codigoEmp);

				      	printf (" \t NOMBRE DE LA EMPRESA: %s \n",emp->nombreEmp);
					  	printf (" \t TIPO DE EMPRESA: %d \n",emp->tipo);
				      	printf (" \t TELEFONO DE LA EMPRESA: %s \n",emp->tlf);
					 	printf (" \t DIRECCION: %s \n",emp->direccion);
				    	printf("--------------------------------------------------------------------------\n\n");
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Se elimina toda la lista de productos de una empresa*/
				void eliminartodoprod(Empresas **emp){
					Productos *tprod, *aux;
					tprod = (*emp)->aba;
						while (tprod){
								aux = tprod;
								tprod = tprod->prox;
								delete aux;
						}
						(*emp)->aba = NULL;
				 }

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para eliminar una empresa, dada la lista y el codigo*/
				void Eliminarempresa(Empresas **emp,int codigo, Personas **per){

					if (*emp){
						if((*emp)->codigoEmp==codigo){
						if ((*emp)->aba) eliminartodoprod(emp); //se deben eliminar toda la lista de productos de esa empresa
						struct empresas *aux=(*emp);
						(*emp)=(*emp)->prox;
						delete (aux);
						system("cls");
						printf("\n\tEmpresa eliminada con exito!!!\n\n");
						Personas *tper = *per;
						Pedidos *ped;
						for (; tper; tper=tper->prox){	//De esta manera eliminamos los pedidos asociados a la empresa eliminada
							ped = tper->aba;
							for (; ped; ped=ped->prox){
								if (ped->codigoEmp == codigo)
								 {
									eliminarenvio(&tper, ped->factura);
								 }

							}
						}
						}
						else
						{
						Eliminarempresa(&(*emp)->prox,codigo, per);
						}
					}
					else
						printf("La empresa no se encuentra en el sistema\n");
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				void prodactivo(bool *act) {
				int valn, activo;
				char copiaactivo[2];
					do {
						do {
							printf("\n 1- Si \n 0- No \n-> ");
							scanf ("%s",&copiaactivo);
							valn=validar_num(copiaactivo);
							if ((strlen(copiaactivo)<1)||(valn!=0))
								printf(" Debe ingresar un numero  \n\n");
						} while ((strlen(copiaactivo)<1)||(valn!=0));
						activo=atoi(copiaactivo);
					} while((activo!=1) && (activo!=0));
					if (activo == 1)*act=true;
					else	*act=false;
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para buscar un producto (solo por codigo) y devuelve la direccion de ese producto*/
				Productos *buscarproductos(Empresas *emp, int codigo) {
					Empresas *temp;
					temp = emp;
					Productos *tprod;
					for ( ; temp ; temp=temp->prox) {
							if (temp->aba) {
								tprod=temp->aba;
								for ( ; tprod ; tprod=tprod->prox) {
										if (tprod->codigoPrt == codigo)  return tprod;	//Se encontro un producto con el mismo codigo
								}
							}
					}
					tprod = NULL;
					return tprod;
				 }

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para buscar un producto (solo por codigo) dentro de una empresa en especifico*/
				Productos *buscarproductosenempresa(Empresas *emp, int codigo) {
					Productos *tprod;
					if (emp->aba) {
						tprod=emp->aba;
						for ( ; tprod ; tprod=tprod->prox) {
								if (tprod->codigoPrt == codigo)  return tprod;	//Se encontro un producto con el mismo codigo
						}
					}
					tprod = NULL;
					return tprod;
				 }

	 			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Funcion para agregar un nuevo producto
				void agregarproducto(Productos **prod, Empresas **emp, int codigo) {

					Productos *tprod;
					tprod = new Productos;
					Empresas *temp;
					char vacio[2];
					temp = buscarempresa(*emp, codigo, vacio, 0);
					printf(" EMPRESA: %s\n\n", temp->nombreEmp);
					do {
						printf(" Introduzca el codigo del producto (1-4 digitos): ");
						ingcodigo(&tprod->codigoPrt);
						printf  (" \n");
						fflush(stdin);
						if (buscarproductosenempresa(temp, tprod->codigoPrt)) printf(" El codigo del producto ya se encuentra registrado en esta empresa \n\n");
					} while (buscarproductosenempresa(temp, tprod->codigoPrt));

					printf (" Introduzca la descripcion del producto [20 caracteres]: ");
					ingnombre(tprod->descripcion);
					printf(" Introduzca el precio por unidad: ");
					ingnum(&tprod->precioUd);
					printf  (" \n");
					fflush(stdin);
					printf(" Indique si el producto esta activo: ");
					prodactivo(&tprod->activo);
					printf("\n");
					tprod->prox = NULL;
					if ((temp->aba)==NULL) {temp->aba = tprod;}
					else {
						Productos *tprod2;
						tprod2 = temp->aba;
						for ( ; tprod2->prox ; tprod2 = tprod2->prox );
						tprod2->prox = tprod;
					}

					printf  (" \n \n");
					system("cls");
					printf("\n\n\tProducto agregado con exito!!!\n\n");

				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dado un producto, muestra todos sus datos*/
				void mostrardatosprod(Productos *prod){

					system("cls");
					if (prod==NULL){
						printf("\n Producto no encontrado en el sistema \n");
					}
					else
					{
						system("cls");
						printf("\n Producto Encontrado en el Sistema \n\n");
						printf("--------------------------------------------------------------------------");
						printf ("\n Los datos del producto son: ");
						printf  (" \n \n");

						printf (" \t CODIGO DEL PRODUCTO: %i  \n",prod->codigoPrt);
						printf (" \t DESCRIPCION DEL PRODUCTO: %s \n",prod->descripcion);
						printf (" \t PRECIO POR UNIDAD: %li \n",prod->precioUd);
						if (prod->activo==true)
							printf (" \t ACTIVO: SI \n");
						else printf (" \t ACTIVO: NO \n");
						printf("--------------------------------------------------------------------------\n\n");
				 }
			  }

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para modificar un Producto*/
				void modificarproducto(Productos *prod) {
				int opmod;

					if (prod) {
							 mostrardatosprod(prod);
							 system("pause");

							do {
								system("cls");
								printf("\n Que campo desea modificar?");
								printf("\n 1- Descripcion  \n 2- Precio \n 3- Actividad \n\n 0- Volver \n");
								fflush(stdin);
								introduciropcion(&opmod);
								system("cls");
								switch (opmod) {
									case 0:
									break;
									case 1:
											printf("\n Descripcion\n\n");
											printf ("\n Introduzca la descripcion del producto [20 caracteres]: ");
											ingnombre(prod->descripcion);
											printf  (" \n");
											fflush(stdin);
									break;
									case 2:
											printf("\n Precio\n\n");
											printf("\n Introduzca el precio por unidad: ");
											ingnum(&prod->precioUd);
											printf  (" \n");
											fflush(stdin);
									break;
									case 3:
											printf("\n Actividad\n\n");
											printf("\n Indique si el producto esta activo:");
											prodactivo(&prod->activo);
									break;
									default:printf("Debe ingresar una opcion valida ");
											sleep(2);
								}
							} while(opmod!=0);
						} else {printf("\n El producto no se encuentra en el sistema \n\n");}
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para eliminar un producto en especifico (por su codigo)*/
				void Eliminarproducto(Empresas **emp, int codigo, Personas **per){

					Empresas *temp;
					temp = *emp;
					Productos *tprod;
					Personas *tper = *per;

						if (temp->aba) {
							tprod=temp->aba;
							if (tprod->codigoPrt == codigo) {		//si el producto a eliminar se encuentra encabezando la lista
								Productos *aux=temp->aba;
								temp->aba = tprod->prox;
								delete aux;
								printf("\n\tProducto eliminado con exito!!!\n\n");
							} else
									for ( ; tprod ; tprod=tprod->prox) {
										if (tprod->prox->codigoPrt == codigo) { 	//si el producto a eliminar no se encuentra encabezando la lista									
											Productos *aux;
											aux = tprod->prox;
											tprod->prox=tprod->prox->prox;
											delete aux;
											printf("\n\tProducto eliminado con exito!!!\n\n");
											break;
										}
									}
						}


			    Pedidos *ped;
					for (; tper; tper=tper->prox){
						ped = tper->aba;
						//se elimina el producto dentro de los pedidos que lo incluyen
						for(; ped; ped=ped->prox){

							if (ped->codigoEmp == (*emp)->codigoEmp){
								eliminarprodinc(&ped, codigo);
								ped->monto_total=PrecioTotal(ped->aba);

								if (!ped->aba)
							  	 {
									eliminarenvio(&tper, ped->factura);   //si el envio queda vacio, este se elimina
								 }

							}
						}
					}

			   }

				 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar todos los productos de una empresa en especifico (por codigo)*/
				 void mostrarproductosemp(Empresas *emp, int codigo){
					 Productos *prod;

					 for ( ; emp; emp=emp->prox){
						 if (codigo==emp->codigoEmp){
							 	prod=emp->aba;
								printf("\n Lista de Productos de '%s'\n", emp->nombreEmp);
							 	for ( ; prod; prod=prod->prox){
									printf("\n--------------------------------------------------------------------------\n");
			 	 					printf (" \t CODIGO DEL PRODUCTO: %i  \n",prod->codigoPrt);
			 	 					printf (" \t DESCRIPCION DEL PRODUCTO: %s \n",prod->descripcion);
			 	 					printf (" \t PRECIO POR UNIDAD: %li \n",prod->precioUd);
			 	 					if (prod->activo==true)
			 	 						printf (" \t ACTIVO: SI \n");
			 	 					else printf (" \t ACTIVO: NO \n");
			 	 					printf("--------------------------------------------------------------------------\n");
						 }
					 }
				 }
				}

 			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 			 /*Funcion para verificar que exista por lo menos un envio (en general o sobre una empresa en especifico)*/
 			 bool existeenvio(Personas *per, int codigo){

 			 	Personas *tper;
				tper = per;
				Pedidos *tped;
					for ( ; tper ; tper=tper->prox) {
							if ((tper->aba) && (codigo==0)) {	//buscar envio en general
							return true;
							}
							else if ((tper->aba) && (codigo!=0)) {	//buscar envio sobre una empresa en especifico
								tped=tper->aba;
								for (; tped; tped=tped->prox)
									if (tped->codigoEmp == codigo) return true;
							}
					}
					return false;
			  }

 			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*Funcion para buscar un pedido (orden de envio) por su numero de factura, y devuelve la direccion de memoria de el nodo encontrado, de caso contrario NULL*/
			Pedidos *buscarenvios(Personas *per, int factura) {
					Personas *tper;
					tper = per;
					Pedidos *tped;
					for ( ; tper ; tper=tper->prox) {
							if (tper->aba) {
								tped=tper->aba;
							for ( ; tped ; tped=tped->prox) {
									if (tped->factura == factura)  return tped;	//Se encontro un pedido con la misma factura
							}
							}
					}
					tped = NULL;
					return tped;
			 }

			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para buscar un producto incluido (Desde la lista dinamica Prodinc) por su numero codigo, y devuelve la direccion de memoria de el nodo encontrado, de caso contrario NULL*/
				Prodinc *buscarprodinc(Prodinc *prodinc, int codigo) {

					for ( ; prodinc ; prodinc=prodinc->prox) {
							if (prodinc->codigoPrt == codigo) return prodinc;	//Se encontro un pedido con la misma factura
					}
					prodinc = NULL;
					return prodinc;
			 }

 			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 			/*Rutina para mostrar todos los productos incluidos de un pedido*/
 			 	void mostrarproductosincluidos (Prodinc *prodinc){

	 			 	printf (" PRODUCTOS EN EL PEDIDO: \n");
						for ( ; prodinc ; prodinc=prodinc->prox) {
						printf ("\n----------------------------------------------------------------------\n");
						printf (" \t CODIGO: ");
						if (prodinc->codigoPrt<10) printf ("000%i ",prodinc->codigoPrt);
						else if (prodinc->codigoPrt<100) printf("00%i ",prodinc->codigoPrt);
				   		else if (prodinc->codigoPrt<1000) printf("0%i ",prodinc->codigoPrt);
						else printf ("%i  ",prodinc->codigoPrt);
						printf ("\t CANTIDAD: %d",prodinc->cantidad);
						printf (" \t PRECIO: %.2f $\n",prodinc->precio);
						printf ("----------------------------------------------------------------------\n");
					 	}

				}
			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para mostrar los datos de un pedido (buscandola por numero de factura)*/
			 void mostrarfactura (Personas *per, int factura){

				 Prodinc *prodinc;
				 Pedidos *ped;
				 Personas *tper;
				 tper = per;

					for ( ; tper ; tper=tper->prox) {

						if (tper->aba) {
							ped=tper->aba;
							for ( ; ped ; ped=ped->prox) {
									if (ped->factura == factura){
										prodinc=ped->aba;
										printf ("\n\t--------------------------------------------------------------------------\n\n");
										printf ("\t                             ORDEN DE ENVIO                             \n\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t--------------------------------------------------------------------------\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t                                  PERSONA                                 \n\n");
										printf ("\t  NOMBRE Y APELLIDO: %s  ", tper->nombre_apellido);
										printf ("\t  \t  \t  CEDULA: %li  \n\n ",tper->cedula);
										printf ("\t  FECHA DE NACIMIENTO: %d/%d/%d ",tper->fechas.anio,tper->fechas.mes,tper->fechas.dia);
										printf ("\t  \t  CIUDAD: %s  \n\n",tper->ciudad);
										printf ("\t  DIRECCION: %s \n\n",tper->direccion);
										printf ("\t--------------------------------------------------------------------------\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t                                  PEDIDO                                  \n\n");
										printf (" \t  \t  \t        NUMERO DE FACTURA: ");
										if (ped->factura<10) printf ("000%i  \n\n",ped->factura);
										else if (ped->factura<100) printf("00%i  \n\n",ped->factura);
				   						else if (ped->factura<1000) printf("0%i  \n\n",ped->factura);
				    					else printf ("%i  \n\n",ped->factura);
										printf (" \t  \t  \t        CODIGO DE LA EMPRESA: ");
										if (ped->codigoEmp<10) printf ("000%i  \n\n",ped->codigoEmp);
										else if (ped->codigoEmp<100) printf("00%i  \n\n",ped->codigoEmp);
				   						else if (ped->codigoEmp<1000) printf("0%i  \n\n",ped->codigoEmp);
				    					else printf ("%i  \n\n",ped->codigoEmp);
										printf ("\t\tFECHA DE EMISION: %d/%d/%d",ped->fechas.dia, ped->fechas.mes, ped->fechas.anio);
										printf (" \t      MONTO TOTAL: %.2f $\n\n", ped->monto_total);
										if (ped->entregados){
										printf (" \t \t \t\t\tENTREGADO: SI \n\n");
										} else { printf (" \t \t \t\t\tENTREGADO: NO \n\n");}
										printf("\t--------------------------------------------------------------------------\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t                                 PRODUCTOS                               \n\n");
										for ( ; prodinc ; prodinc=prodinc->prox) {
											printf ("\t    CODIGO: ");
											if (prodinc->codigoPrt<10) printf ("000%i ",prodinc->codigoPrt);
											else if (prodinc->codigoPrt<100) printf("00%i ",prodinc->codigoPrt);
				   							else if (prodinc->codigoPrt<1000) printf("0%i ",prodinc->codigoPrt);
				    						else printf ("%i  ",prodinc->codigoPrt);
											printf (" \t \tCANTIDAD: %d",prodinc->cantidad);
											printf (" \t \tPRECIO: %.2f $\n",prodinc->precio);
											printf ("\t--------------------------------------------------------------------------\n\n");
										}
										system("pause");
										break;
									}  ;
									}
							}
					}

					if (ped==NULL){
					 printf("\n El numero de factura no se encuentra en el sistema ");
					 return;}
			 }

			 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para agregar un producto en un envio especifico*/
			void agregarproductoincluido (Prodinc **prodinc, Empresas *emp){
			int codigo2;
			Productos *prod;

			printf("\n Ingrese el codigo del producto a agregar: ");
			ingcodigo(&codigo2);

				//Buscamos el producto dentra de la empresa
				prod = buscarproductosenempresa(emp, codigo2);
				//Debemos verificar que el producto que desea agregar el usuario se encuentre dentro de la lista de productos de la empresa elegida
				if ((!prod) || (prod->activo==false)){
					printf("\n El producto no existe o no esta activo\n");
					system("pause");
					return;
				};
				Prodinc *x;
				x = buscarprodinc(*prodinc, codigo2);
				if (x){
						printf("\n El producto que desea ingresar, ya esta incluido\n Actualmente tiene: %i unidad/es \n\n ", x->cantidad);
						system("pause");
						return;
				};
				//Al saber que el producto existe y esta activo, creamos el nodo de productos incluidos y lo llenamos
				Prodinc *prodinccopia;
				prodinccopia = new Prodinc;
				prodinccopia->codigoPrt = codigo2;
				printf("\n Cantidad: ");
				ingcodigo(&prodinccopia->cantidad);
				prodinccopia->precio = prod->precioUd;
				prodinccopia->prox = NULL;
			    //se agrega el nuevo nodo de detalleproductosincluidos
				if (*prodinc == NULL){	//if el pedido no tiene ningun producto
					*prodinc=prodinccopia;
				} else {				//else se agrega el nuevo producto por cola
						Prodinc *cola;
						cola = *prodinc;
						for ( ; cola->prox; cola=cola->prox);
							cola->prox=prodinccopia;
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para agregar un envio*/
			 void agregarenvio(Personas **per, Empresas *emp){

			 	long int copiacedula;
			 	printf(" Quien desea hacer el pedido? (ingrese su cedula): ");
				ingnum(&copiacedula);
				Personas *tper;
			 	tper = buscarpersona(*per, copiacedula, vacio);
			 	 if (tper==NULL) {
				 	printf("\n La cedula ingresada no se encuentra en el sistema\n\n");
				 	printf(" Regresara al menu anterior\n\n");
				 	system("pause");
				 	return;
				 }

				 int tipo, codigo, codigo2, op, equiv;
				 equiv=2;

				 printf("\n PERSONA: %s\n\n", tper->nombre_apellido );

				do {
					 printf (" Introduzca el tipo de empresa: \n");
					 printf(" 1- Comidas\n 2- Alimentos\n 3- General \n ->");
					 ingtipo(&tipo);

					 	if (buscarempresa(emp, 0, vacio, tipo) == NULL) {
					 		equiv--;
				 			printf("\n No existe ninguna empresa de ese tipo\n Tiene %i intento/s para regresar\n\n", equiv);
				 			if (equiv==0){
				 				printf("\n Regrasara al menu\n\n");
				 				system("pause");
							  return;}
						 }
			    } while (buscarempresa(emp, 0, vacio, tipo) == NULL);

			    equiv=2;
				printf("\n Empresas de tipo %i: \n", tipo);
				mostrartodoemp(emp, tipo);
				Empresas *xemp;
				do {
				 	printf("\n Introduzca el Codigo de la Empresa: ");
				 	ingcodigo(&codigo);
				 	//Buscamos la empresa con el codigo ingresado
				 	xemp = buscarempresa(emp, codigo, vacio, 0);
				 	if (xemp==NULL){
				 		printf("\n El codigo de la empresa que ha ingresado no se encuentra en el sistema\n\n");
				 		system("pause");
				 		return;
					 }
				 	if (xemp->tipo!=tipo){
					 		equiv--;
					 		printf("\n El codigo de empresa que ha ingresado no se encuentra dentro de las empresas tipo '%i'\n", tipo);
					 		printf(" Tiene %i intento/s para regresar\n\n",equiv);
				 			if (equiv==0){
				 				printf("\n Regrasara al menu\n\n");
				 				system("pause");
							  return;}
					}
				} while (xemp->tipo!=tipo);

				    if (xemp->aba==NULL) {
						 	printf("\n La Empresa seleccionada no tiene ningun producto\n\n");
						 	printf(" Regresara al menu anterior\n\n");
					 		system("pause");
					 		return;
						 }

				Productos *prod;
				Pedidos *ped;
				ped = new Pedidos;
				ped->entregados = false;
				Prodinc *prodinc;
				prodinc = NULL;
				system("cls");
				do {
						mostrarproductosemp(emp, codigo);
						printf("\n Que desea hacer?\n");
						printf("\n 1- Agregar \n");
						if (prodinc) printf(" 0- Continuar Pedido");
						fflush(stdin);
						introduciropcion(&op);
						switch(op){
							case 0: break;
							case 1: system("cls");
									printf("\n\tAGREGAR\n");
									mostrarproductosemp(emp, codigo);
									agregarproductoincluido (&prodinc, xemp);
							break;
							default:
							printf(" Debe elegir una opcion valida\n");
						}
				   system("cls");
				} while ((op!=0)||(prodinc==NULL));
				//una vez ingresados todos los productos del pedido, se incluyen (detalles de productos incluidos) al pedido (por "aba")
				//y se llena el pedido

				printf("\n\tCONTINUAR PEDIDO\n\n");
				ped->aba=prodinc;
				ped->codigoEmp=codigo;
				printf (" Introduzca la fecha de hoy:  \n");
				ingfecha(&ped->fechas.anio, &ped->fechas.mes, &ped->fechas.dia);

				 //Recorremos toda la lista de productos del pedido para hallar la suma total
				 ped->monto_total=PrecioTotal(ped->aba);
				do{
					 printf(" Introduzca su numero de factura: ");
					 ingcodigo(&ped->factura);
					 	 if (buscarenvios(*per, ped->factura)) {
							 printf("\n Ese numero de factura ya se encuentra en el sistema\n\n");
						 }
			    } while (buscarenvios(*per, ped->factura));

				//por ultimo, se le asigna el pedido a la persona
				if (tper->aba){	//if no es el primer envio de la persona
					 ped->prox = tper->aba; //se inserta el nuevo envio por cabeza
				};
				tper->aba = ped; //se actualiza el nuevo puntero cabeza como multilista
				system("cls");
				printf("\n\n\tPedido agregado con exito!!!\n\n");
				system("pause");
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para cerrar un envio*/
			void cerrarenvio (Personas **per, int copiafactura ){
				Pedidos *ped;
				ped=buscarenvios(*per, copiafactura);

					if (ped==NULL){
						printf("\n No existe ningun pedido con ese numero de factura en el sistema\n\n");
						system("pause");
						return;
					}
					if (ped->entregados==true){
						printf("\n El pedido ya ha sido entregado\n\n");
						system("pause");
						return;
					}
				ped->entregados=true;
				printf("\n Pedido '%i' entregado \n\n", copiafactura);
				system("pause");
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar un producto incluido (especifico) en un pedido, (por su codigo)*/
			void eliminarprodinc (Pedidos **ped, int codigo){

				Prodinc *x;
				x = (*ped)->aba;
				for ( ; x; x=x->prox){

					if (x->codigoPrt == codigo){	//si el producto inc esta de cabeza en la lista
						Prodinc *y;
						y=x;
						x=x->prox;
						delete y;
						(*ped)->aba = x;
						return;
					}
					if (x->prox)	//x->prox debe existir
						if (x->prox->codigoPrt == codigo){ // si no esta de cabeza en la lista
							Prodinc *y;
							y = x->prox;
							x->prox = x->prox->prox;
							delete y;
							return;
						}
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			void Modificarenvio (Personas **per, int copiafactura, Empresas *emp){
				Pedidos *ped;
				int opmod, codigo2;

				ped=buscarenvios(*per, copiafactura);

				//no se puede modificar un pedido ya entregado
				if (ped->entregados==true){
					printf("\n El pedido que desea modificar ya esta entregado \n\n");
					system("pause");
					return;
				}

				Prodinc *prodinc;
				prodinc = ped->aba;

				Productos *prod;

				mostrarfactura (*per, copiafactura);

						do {
							system("cls");
							printf("\n Que campo desea modificar?");
							printf("\n 1- Agregar  \n 2- Eliminar \n 3- Modificar Cantidad \n\n 0- Finalizar \n");

									fflush(stdin);
									introduciropcion(&opmod);
									system("cls");

									switch (opmod) {
										case 0:
										break;
										case 1:
												printf("\n Agregar\n\n");
												mostrarproductosemp(emp, ped->codigoEmp);
												agregarproductoincluido (&prodinc, buscarempresa(emp,ped->codigoEmp, vacio, 0));
										break;
										case 2:
												printf("\n Eliminar\n\n");
												if (prodinc->prox==NULL){
													printf(" No puedes eliminar el ultimo producto de este envio\n Puede eliminar el envio en el menu (3.5- envios) \n\n");
													system("pause");
													break;
												}
												mostrarproductosincluidos (ped->aba);
												printf("\n Ingrese el codigo del producto a eliminar: ");
												ingcodigo(&codigo2);
												if (!(buscarprodinc(prodinc, codigo2))){
													printf("\n No se encuentra ningun producto con ese codigo en su pedido\n\n");
													system("pause");
													break;
												}
												eliminarprodinc(&ped, codigo2);
												prodinc=ped->aba;
												system("cls");
												printf("\n\tProducto eliminado del pedido con exito!!!\n\n");
												system("pause");
										break;
										case 3:
												printf("\n Modificar Cantidad\n\n");
												Prodinc *x;
												mostrarproductosincluidos (ped->aba);
												printf("\n Ingrese el codigo del producto a modificar: ");
												ingcodigo(&codigo2);
												x = buscarprodinc(prodinc, codigo2);
												if (x==NULL){
													printf("\n No se encuentra ningun producto con ese codigo en su pedido\n\n");
													system("pause");
													break;
												}
												prod = buscarproductos(emp, codigo2); //Se puede usar buscarproductosenempresas
												printf("\n Ingrese la nueva cantidad de su producto: ");
												ingcodigo(&x->cantidad);
												//x->precio = (prod->precioUd * x->cantidad);
												x->precio = prod->precioUd;
												system("cls");
												printf("\n\tCantidad modificada con exito!!! \n\n");
												system("pause");
										break;
										default: printf("Debe ingresar una opcion valida ");
												sleep(2);
									}

						} while(opmod!=0);

					//actualizamos el monto total del pedido
					ped->monto_total=PrecioTotal(ped->aba);

					printf("\n\t Envio modificado con exito!!!\n\n");
					system("pause");

				}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar todos los productos incluidos de un envio*/
			void eliminartodoprodinc(Pedidos **ped){
				Prodinc *prodinc, *aux;
				prodinc = (*ped)->aba;

					while (prodinc){
							aux = prodinc;
							prodinc = prodinc->prox;
							delete aux;
					}
				(*ped)->aba = NULL;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar todos los envios realizados por una persona*/
			void eliminartodoenvio(Personas **per){
				Pedidos *ped, *aux;
				ped = (*per)->aba;

					while (ped){
							eliminartodoprodinc(&ped);
							aux = ped;
							ped = ped->prox;
							delete aux;
					}
				(*per)->aba = NULL;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar un envio en especifico (por su factura)*/
			void eliminarenvio(Personas **per, int factura){

				Pedidos *xped;
				Personas *xper = *per;
				xped = xper->aba;

				for ( ; xped; xped=xped->prox){
					if (xped->factura == factura){ //si el envio esta en cabeza
						Pedidos *yped;
						eliminartodoprodinc(&xped);
						yped=xped;
						xped=xped->prox;
						delete yped;
						(*per)->aba = xped;
						return;
					}
					if (xped->prox)
						if (xped->prox->factura == factura){ // si el envio no esta en cabeza
							Pedidos *yped;
							yped = xped->prox;
							eliminartodoprodinc(&yped);
							xped->prox = xped->prox->prox;
							delete yped;
							return;
						}
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion auxiliar para eliminar un envio, donde se verifican los dartos ingresados antes de eliminar el envio requerido*/
			void eliminarenvioaux(Personas **per){

					int copiacod, copiafactura;
					long int copiacedula;

					printf(" Ingrese el numero de factura: ");
					ingcodigo(&copiafactura);
					printf("\n");
					printf(" Ingrese la cedula de la persona que realizo el envio: ");
					ingnum(&copiacedula);
					printf("\n");
					printf(" Ingrese el codigo de la empresa relacionada al envio: ");
					ingcodigo(&copiacod);
					printf("\n");

					Personas *xper;

					xper = buscarpersona(*per, copiacedula, vacio);

					if (xper==NULL){
						printf("\n La cedula ingresada no encuentra en el sistema\n\n");
						system("pause");
						return;
					}

					Pedidos *ped, *xped;
					ped = xper->aba;
					xped = xper->aba;

					for ( ; xped ; xped=xped->prox) {
						if ((xped->codigoEmp==copiacod)&&(xped->factura==copiafactura)) {
							break;
						}
					}

					if (xped==NULL){
						printf("\n La persona indicada no ha realizado un envio donde coincidan el codigo de la empresa y/o factura indicada\n\n");
						system("pause");
						return;
					}

					eliminarenvio(&xper, copiafactura);
					system("cls");
					printf("\n Envio eliminado con exito!!!\n\n");
					system("pause");

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				void Datosemp(int codigo, Personas *per, int *entt, int *noentt, int *clientest, float *ingtotalt, float *promgastadot, int *clientesverift){

						Personas *tper;
						tper = per;
						Pedidos *ped;

						int ent, noent, clientes, clientesverif;
						ent = 0;
						noent = 0;
						clientes = 0;
						clientesverif = 0;

						long int cedula, cedula2;
						cedula = 0;
						cedula2 = 0;

						float ingtotal, promgastado;
						ingtotal = 0;
						promgastado = 0;

						for (; tper; tper=tper->prox){

							ped = tper->aba;

							for ( ; ped; ped=ped->prox){

								if (ped->codigoEmp == codigo){

									if (ped->entregados){
										ent++;
										ingtotal+=ped->monto_total;

											if (cedula2 != tper->cedula){	//necesitamos un contador de clientes verificados
											clientesverif++;				//donde solo cuenten clientes con minimo 1 pedido entregado
											cedula2 = per->cedula;
											}
									}else {
										noent++;
									}

									if (cedula != tper->cedula){
									clientes++;

									}
									// de esta manera solo contamos una vez al cliente
									cedula = tper->cedula;

								}
							}
						}
					if (clientesverif !=0)
					promgastado = ingtotal/clientesverif;

					printf(" PEDIDOS ENTREGADOS: %i - PEDIDOS NO ENTREGADOS: %i - CLIENTES ATENDIDOS: %i - INGRESO TOTAL VENDIDO: %.2f$ - PROMEDIO DE GASTO POR CLIENTE: %.2f$ \n\n", ent, noent, clientes, ingtotal, promgastado);

							*entt += ent;
							*noentt += noent;
							*clientest += clientes;
							*ingtotalt += ingtotal;
							*clientesverift += clientesverif;

					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para contar el total de ventas de una empresa*/
					int totalventas(Personas *per,int codigo){

						Personas *tper = per;
						Pedidos *ped;
						int total = 0;

							for ( ; tper; tper=tper->prox){
									ped = tper->aba;
									for ( ; ped; ped=ped->prox){
										if (ped->codigoEmp==codigo){
											if (ped->entregados) total++;
										}
									}
							}
						return total;
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para contar el ingreso total vendido entregado o no entregado*/
					float totaling(Personas *per,int codigo, int i){
						// i == 1 -> total vendido entregado
						// i == 2 -> total vendido no entregado

						Personas *tper = per;
						Pedidos *ped;
						float total = 0;
						float totalno = 0;

							for ( ; tper; tper=tper->prox){
									ped = tper->aba;
									for ( ; ped; ped=ped->prox){
										if (ped->codigoEmp==codigo){
											if (ped->entregados) total += ped->monto_total;
											if (!ped->entregados) totalno += ped->monto_total;
										}
								 }
							}
						if (i==1){
					 	return total;
						} else {
						return totalno;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Funcion para conocer el promedio de cantidad de productos por factura*/
					float promedioproducto(Personas *per,int codigo){

						Personas *tper = per;
						Pedidos *ped;
						Prodinc *prodinc;
						int productos = 0;
						int pedidos = 0;

							for ( ; tper; tper=tper->prox){
									ped = tper->aba;
									for ( ; ped; ped=ped->prox){
										if (ped->codigoEmp==codigo){
												pedidos++;
												prodinc = ped->aba;
												for ( ; prodinc; prodinc=prodinc->prox) productos += prodinc->cantidad;
										}
								 }
							}
						return (productos/pedidos);
					}
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina swap */
					void swap(long int* a, long int* b){
						int c = *a;
						*a = *b;
						*b = c;
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina del metodo de ordenamiento burbuja*/
					void BurbujaEnteros(long int* const arrayInt, int nroElementosInt){
						int contadorDeIntercambios;
						for (int i = 0; i < nroElementosInt - 1; i++)
						{
							contadorDeIntercambios = 0;
							for (int j = 0; j < nroElementosInt - 1; j++)
								if (arrayInt[j] < arrayInt[j + 1])
								{
									contadorDeIntercambios++;
									swap(arrayInt + j, arrayInt + j + 1);
								}
							if (contadorDeIntercambios == 0)
								break;
						}

					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina que dada una empresa muestra informacion de ella y sus clientes*/
					void infodeunaemp(Empresas *emp, Personas *per){

						int consulta;
						Personas *tper = per;

						Personas *xper;
						Pedidos *xped;
						Prodinc *xprodinc;

						printf("\n Como desea ordenar los clientes?\n");
						printf(" 1- Cedula\n 2- Cantidad de pedidos \n");

						do {
							fflush(stdin);
							introduciropcion(&consulta);
						} while(consulta!=1 && consulta!=2);

						system("cls");

						printf("\n\t INFORMACION DE UNA EMPRESA/n/n");

						printf("\n EMPRESA:\n NOMBRE: %s \n", emp->nombreEmp);
						printf(" CANTIDAD TOTAL DE VENTAS: %i - INGRESO TOTAL VENDIDO: %.2f$ - TOTAL DE INGRESO NO ENTREGADO: %.2f$ - PROMEDIO DE CANTIDAD DE PRODUCTOS POR FACTURA: %.2f \n\n", totalventas(per,emp->codigoEmp), totaling(per, emp->codigoEmp, 1), totaling(per, emp->codigoEmp, 2), promedioproducto(per, emp->codigoEmp));

						printf("---------------------------------------------------------------------\n");
						printf("---------------------------------------------------------------------\n\n");

						int a = 0;
						tper = per;
						for (; tper ; tper=tper->prox) a++;
						long int array[a+1];

						tper = per;
						switch (consulta){
							case 1:	//Por CEDULA
								//llenamos el arreglo con las cedulas, y las ordenamos por burbuja
								for (int x=0; tper; tper=tper->prox, x++) array[x] = tper->cedula;
								BurbujaEnteros(array, a);

							break;
							case 2: //por cantidad de pedidos (Entregados como no entregados)
								//llenamos el arreglo con la cantidad de pedidos de cada persona, y las ordenamos por burbuja
								for (int x=0; tper; tper=tper->prox, x++){
									int cped = 0;
									xped = tper->aba;
									for (; xped; xped=xped->prox)
										if (xped->codigoEmp == emp->codigoEmp) cped++;
									array[x] = cped;
								}
								BurbujaEnteros(array, a);

								//Buscamos la persona con la misma cantidad de pedidos
								for (int x=0 ; x<a ; x++){
									tper = per;

									for (; tper; tper = tper->prox){
										bool repe = false;
										long int i = 0;
										int cped=0;
										xped = tper->aba;

										for (; xped; xped=xped->prox)
											if (xped->codigoEmp == emp->codigoEmp) cped++;

										//Verificamos que la persona encontrada no este repetida (en caso que dos o mas personas tengan la misma cantidad de pedidos)
										if (x==0){
											if (cped == array[x]){
											i = tper->cedula;
											array[x] = i;
											break;
											}
										} else{
											for (int y=0 ; y<x ; y++){
												if (array[y] == tper->cedula) {
												repe = true;
												break;
												}
											}
											if ((cped == array[x]) && (!repe)) {
												i = tper->cedula;
												array[x] = i;
												break;
											}
										}
									}
								}
							break;
						}
							printf(" CLIENTE/S:\n");
							for (int x=0; x<a; x++){
								float facturado = 0;
								int cprod = 0;

								xper=buscarpersona(per, array[x], vacio);
								xped = xper->aba;
									for ( ; xped ; xped=xped->prox){
										if (xped->codigoEmp == emp->codigoEmp){
											facturado += xped->monto_total;
											xprodinc=xped->aba;
												for ( ; xprodinc; xprodinc=xprodinc->prox){
													cprod += xprodinc->cantidad;
												}
										}
									}
								if (facturado != 0) printf(" NOMBRE: %s - CEDULA: %li - TOTAL FACTURADO: %.2f$ - CANTIDAD DE PRODUCTOS: %i \n\n",xper->nombre_apellido, xper->cedula, facturado, cprod );
							}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dado la cedula de una persona, muestra los detalles de cada pedido */
					void infocliente(Personas *per){
					Personas *tper=per;
					long int copiacedula;
					Pedidos *ped;
					float totalpercibido=0;
					int prodentregados=0;
					bool existe = false;

					printf(" Ingrese la cedula del cliente: ");
					ingnum(&copiacedula);

					tper = buscarpersona(per, copiacedula, vacio);

					if (tper==NULL){
						printf("\n La cedula ingresada no se encuentra en el sistema\n\n");
						return;
					}

					printf("\n\tDATOS DEL CLIENTE\n\n");
					printf(" NOMBRE: %s - CEDULA: %li",tper->nombre_apellido,tper->cedula);
					ped=tper->aba;

					if (!ped){
						printf("\n\n El cliente no tienen ningun pedido \n\n");
						return;
					}

					printf("\n\n\tPEDIDOS ENTREGADOS \n\n");
					for( ;ped;ped=ped->prox){
						int cantidad=0;
						if(ped->entregados){
							existe = true;
							Prodinc *prodinc=ped->aba;
							totalpercibido+=ped->monto_total;
							for(;prodinc;prodinc=prodinc->prox){
								cantidad+=prodinc->cantidad;
								prodentregados+=prodinc->cantidad;
							}
							//Se puede agregar la fecha como detalle//
							printf(" ENVIO: %i - ENTREGADO: SI - CANT.DE PRODUCTOS: %i - EMPRESA: %i - MONTO TOTAL: %.2f$\n - FECHA: %i/%i/%i ",ped->factura,cantidad,ped->codigoEmp,ped->monto_total,ped->fechas.dia,ped->fechas.mes,ped->fechas.anio);
						}
					}
					if (!existe) printf(" Este cliente no posee pedidos entregados\n");

					printf("\n---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n");
					existe = false;

					ped=tper->aba;
					printf("\n\t PEDIDOS NO ENTREGADOS \n\n");
					for( ;ped;ped=ped->prox){
						int cantidad=0;
						if(!ped->entregados){
							existe = true;
							Prodinc *prodinc=ped->aba;
							for(;prodinc;prodinc=prodinc->prox){
								cantidad+=prodinc->cantidad;

							}
							printf(" ENVIO: %i - ENTREGADO: NO - CANT.DE PRODUCTOS: %i - EMPRESA: %i - MONTO TOTAL: %.2f$ - FECHA: %i/%i/%i \n\n",ped->factura,cantidad,ped->codigoEmp,ped->monto_total,ped->fechas.dia,ped->fechas.mes,ped->fechas.anio);
						}
					}

					if (!existe) printf("   Todos los pedidos de este cliente han sido entregados\n\n");

					printf("---------------------------------------------------------------------\n");
					printf("\n TOTAL DE INGRESO PERCIBIDO: %2.f$ - CANT.PRODUCTOS ENTREGADOS: %i \n",totalpercibido,prodentregados);
					return;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para calcular el mejor cliente por cantidad total percibida*/
				void mejorclientetotal(Personas *per){
					Personas *tper=per;
					Personas *percopia=NULL;
					Pedidos *ped;
					float mayor,montototal;
					mayor=1;

					for( ;tper;tper=tper->prox){
						ped=tper->aba;
						montototal=0;
						for( ;ped ;ped=ped->prox){
							if (ped->entregados) montototal+=ped->monto_total;
						}
						if (montototal>mayor){
							mayor=montototal;
							percopia=tper;
						}
					}

					printf(" MEJOR CLIENTE POR CANTIDAD TOTAL PERCIBIDA \n");

						if (!percopia){
						printf("\n NO EXISTEN CLIENTES CON PEDIDOS ENTREGADOS\n\n\n");
						return;
						}

					printf("\n NOMBRE: %s - ",percopia->nombre_apellido);
					printf("CEDULA: %li\n",percopia->cedula);
					printf("\n\n");

					return;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para calcular el mejor cliente por la cantidad de productos comprados */
					void mejorclienteproductos (Personas *per){

					Personas *tper=per;
					Pedidos *ped;
					Prodinc *prodinc;
					Personas *copiapersona=NULL;
					int cantidad;
					int mayor=1;

					for(;tper;tper=tper->prox){
						ped=tper->aba;
						cantidad=0;
						for(;ped;ped=ped->prox){
							prodinc=ped->aba;
							for(;prodinc;prodinc=prodinc->prox){

								if (ped->entregados) cantidad+=prodinc->cantidad;
							}
						}

						if (cantidad>mayor){
							mayor=cantidad;
							copiapersona=tper;
						}
					}

					printf(" MEJOR CLIENTE POR CANTIDAD DE PRODUCTOS COMPRADOS \n");

						if (!copiapersona){
						printf("\n NO EXISTEN CLIENTES CON PEDIDOS ENTREGADOS\n\n\n");
						return;
						}

					printf("\n NOMBRE: %s - ",copiapersona->nombre_apellido);
					printf("CEDULA: %li\n",copiapersona->cedula);
					printf("\n\n");

					return;
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para calcular el peor cliente por cantidad total NO percibida*/
						void peorclientetotal(Personas *per){
							Personas *tper=per;
							Personas *percopia=NULL;
							Pedidos *ped;
							float mayor,montototal;
							mayor=0;


							for( ;tper;tper=tper->prox){
								ped=tper->aba;
								montototal=0;
								for( ;ped ;ped=ped->prox){
									if (!ped->entregados) montototal+=ped->monto_total;
								}
								if (montototal>mayor){
									mayor=montototal;
									percopia=tper;
								}
							}

							printf(" PEOR CLIENTE POR CANTIDAD TOTAL NO PERCIBIDA \n");

								if (!percopia){
								printf("\n NO EXISTEN CLIENTES CON PEDIDOS NO ENTREGADOS\n\n\n");
								return;
								}

							printf("\n NOMBRE: %s - ",percopia->nombre_apellido);
							printf("CEDULA: %li\n",percopia->cedula);
							printf("\n\n");

							return;
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para calcular el peor cliente por la cantidad de productos NO comprados */
					void peorclienteproductos (Personas *per){

					Personas *tper=per;
					Pedidos *ped;
					Prodinc *prodinc;
					Personas *copiapersona=NULL;
					int cantidad;
					int mayor=0;

					for(;tper;tper=tper->prox){
						ped=tper->aba;
						cantidad=0;
						for(;ped;ped=ped->prox){
							prodinc=ped->aba;
							for(;prodinc;prodinc=prodinc->prox){

								if (!ped->entregados) cantidad+=prodinc->cantidad;
							}
						}

						if (cantidad>mayor){
							mayor=cantidad;
							copiapersona=tper;
						}
					}

					printf(" PEOR CLIENTE POR CANTIDAD DE PRODUCTOS NO COMPRADOS \n");

						if (!copiapersona){
						printf("\n NO EXISTEN CLIENTES CON PEDIDOS NO ENTREGADOS\n\n\n");
						return;
						}

					printf("\n NOMBRE: %s - ",copiapersona->nombre_apellido);
					printf("CEDULA: %li\n",copiapersona->cedula);
					printf("\n\n");

					return;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que cuenta la cantidad pedida (Entregada o no dependiendo de su opcion) de un producto en especifico*/
				int contarprod(Personas *per, int codigoPrt, int codigoEmp, int opcion){
					//opcion = 1 cuenta la cantidad comprada de un producto
					//opcion = 2 cuenta la cantidad de un producto no entregado

					Personas *tper = per;
					Pedidos *ped;
					Prodinc *prodinc;
					int cantidad = 0;

					for (; tper; tper=tper->prox){
						ped = tper->aba;

							for (; ped; ped=ped->prox){

								if (opcion == 1)
									if ((ped->codigoEmp == codigoEmp) && (ped->entregados)) {
										prodinc = ped->aba;

										for ( ; prodinc; prodinc=prodinc->prox){
											if (prodinc->codigoPrt == codigoPrt) cantidad += prodinc->cantidad;
										}
									}
								if (opcion == 2)
									if ((ped->codigoEmp == codigoEmp) && (!ped->entregados)) {
										prodinc = ped->aba;

										for ( ; prodinc; prodinc=prodinc->prox){
											if (prodinc->codigoPrt == codigoPrt) cantidad += prodinc->cantidad;
										}
									}
							}
					}

					return cantidad;
				}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra los mejores productos (mas vendido y mejor ingreso)*/
				void mejoresprod(Empresas *emp, Personas *per){
					Empresas *temp = emp;
					Productos *prod;
					Productos *xprod=NULL;
					Empresas *xemp;
					int i=0;
					int mayor=0;

					long int j=0;
					long int mayorgenerado=0;
					long int cantidad=0;
					Productos *yprod;
					Empresas *yemp;

					for ( ; temp; temp=temp->prox){
						prod = temp->aba;

						for ( ; prod; prod=prod->prox){

							i = contarprod(per, prod->codigoPrt, temp->codigoEmp, 1);

							j = i*prod->precioUd;

							//actualizamos el producto con mayor cantidad
							if (i>mayor){
							 mayor = i;
							 xprod = prod;
							 xemp = temp;
							}

							//actualizamos el producto con mayor ingreso generado
							if (j>mayorgenerado){
							 cantidad = i;
							 mayorgenerado = j;
							 yprod = prod;
							 yemp = temp;
							}
						}
					}

					printf("---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n\n");
					if (xprod == NULL){
					printf(" Ningun pedido ha sido entregado\n\n");
					return;
					}

					printf(" PRODUCTO MAS VENDIDO \n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", xemp->nombreEmp, xprod->descripcion, mayor, (float)xprod->precioUd*(float)mayor);
					printf("---------------------------------------------------------------------\n\n");
					printf(" PRODUCTO CON MEJOR INGRESO \n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", yemp->nombreEmp, yprod->descripcion, cantidad , (float)yprod->precioUd*(float)cantidad);
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra los peores productos (menos vendido y peor ingreso)*/
				void peoresprod(Empresas *emp, Personas *per){

					Empresas *temp = emp;
					Productos *prod;
					Productos *xprod = NULL;
					Empresas *xemp;
					int i=maxint;
					int menor=maxint;

					long int j=maxlongint;
					long int menorgenerado=maxlongint;
					long int cantidad=maxlongint;
					Productos *yprod;
					Empresas *yemp;

					for ( ; temp; temp=temp->prox){
						prod = temp->aba;

						for ( ; prod; prod=prod->prox){

							i = contarprod(per, prod->codigoPrt, temp->codigoEmp, 2);

							if (i!=0){	//evitamos caso borde, donde el producto no se encuentra en ningun pedido (no entregado)

								j = i*prod->precioUd;

								//actualizamos el producto con menor cantidad
								if (i<menor){
								 menor = i;
								 xprod = prod;
								 xemp = temp;
								}

								//actualizamos el producto con menor ingreso generado
								if (j<menorgenerado){
								 cantidad = i;
								 menorgenerado = j;
								 yprod = prod;
								 yemp = temp;
								}
							}
						}
					}

					printf("---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n\n");

					if (xprod == NULL){
					printf(" Todos los pedidos del cliente han sido entregados\n\n");
					return;
					}

					printf(" PRODUCTO MENOS VENDIDO (NO ENTREGADO)\n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", xemp->nombreEmp, xprod->descripcion, menor, (float)xprod->precioUd*(float)menor);
					printf("---------------------------------------------------------------------\n\n");
					printf(" PRODUCTO CON PEOR INGRESO (NO ENTREGADO) \n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", yemp->nombreEmp, yprod->descripcion, cantidad , (float)yprod->precioUd*(float)cantidad);

					printf("---------------------------------------------------------------------\n\n");

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra informacion de una persona relacionada a una empresa*/
				void infopersona_empresa (Personas *per, Empresas *emp){
					Pedidos *ped;
					Prodinc *prodinc;
					int totalped = 0;
					int totalpedno = 0;
					int totalprod = 0;
					int totalprodno = 0;
					float montoprod = 0;
					float montoprodno = 0;

					ped = per->aba;
					for (; ped; ped=ped->prox){

						if (ped->codigoEmp == emp->codigoEmp){	//solo debemos tomar en cuenta los pedidos de una empresa en especifico

							if (ped->entregados){
								totalped++;
								montoprod += ped->monto_total;
							} else {
								totalpedno++;
								montoprodno += ped->monto_total;
							}

							prodinc=ped->aba;
							for (; prodinc; prodinc=prodinc->prox){

								if (ped->entregados) {
								totalprod += prodinc->cantidad;
								} else {
							 	totalprodno += prodinc->cantidad;
								}
							}
						}
					}

					printf(" EMPRESA: %s - TOTAL DE FACTURAS: ENTREGADAS: %i - NO ENTREGADAS: %i - CANTIDAD DE PRODUCTOS: ENTREGADOS: %i - NO ENTREGADOS: %i - MONTO TOTAL DE FACTURAS: ENTREGADAS: %.2f$ - NO ENTREGADAS: %.2f$ \n\n", emp->nombreEmp, totalped, totalpedno, totalprod, totalprodno, montoprod, montoprodno );
					printf("---------------------------------------------------------------------\n\n");

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dada una persona muestra el total de: pedidos hechos, productos adquiridos, monto pagado por los productos. Luego
				se muestran la(s) empresa(s) con el total de facturas, las cantidades de productos y monto de cdaa uno*/
				void infodeunaper(Personas *per, Empresas *emp){

					Pedidos *ped;
					Prodinc *prodinc;
					int totalped = 0;
					int totalprod = 0;
					int totalprodno = 0;
					float montoprod = 0;
					float montoprodno = 0;

					mostrardatospersona(per);

					if (!per->aba) {
						printf(" La persona no ha realizado ningun pedido\n\n");
						return;
					}

					ped = per->aba;

					for( ; ped; ped=ped->prox , totalped++){
						prodinc = ped->aba;

						if (ped->entregados) montoprod += ped->monto_total;
						else montoprodno += ped->monto_total;

						for (; prodinc; prodinc=prodinc->prox){

							if (ped->entregados) {
								totalprod += prodinc->cantidad;
							} else {
							 	totalprodno += prodinc->cantidad;
							}
						}
					}

					printf(" TOTAL DE PEDIDOS HECHOS: %i - TOTAL DE PRODUCTOS: ADQUIRIDOS: %i - NO ADQUIRIDOS: %i - MONTO DE PRODUCTOS: PAGADOS: %.2f$ - NO PAGADOS: %.2f$ \n\n", totalped, totalprod, totalprodno, montoprod, montoprodno );
					printf("---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n\n");

					ped = per->aba;

					printf(" INFORMACION DE CADA EMPRESA: \n\n");
					printf("---------------------------------------------------------------------\n\n");

					//hacer arreglo con codigos de empresa de los pedidos, de esta manera evitar repetir codigos
					// y hacer el mismo for, pero recorriendo ese arreglo
					int a=0;
					for( ;ped;ped=ped->prox){
						a++;
					}

					ped = per->aba;
					int array[a+1];
					for (int x=0; ped;ped=ped->prox, x++){
						int c=0;

						for(int i=0;i<a;i++){
							if(array[i]==ped->codigoEmp) c++;
						}
						if (c==0) array[x]=ped->codigoEmp;
					}

					for(int x=0 ; x<a; x++){
						if (array[x] != 0)
						infopersona_empresa(per, buscarempresa(emp, array[x], vacio, 0));
					}

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra la informacion de una personas (y sus pedidos) en relacion a una empresa, de forma detallada */
				void infopersona_empresadetallada(Personas *per, Empresas *emp){
						Pedidos *ped;
						Prodinc *prodinc;
						int totalped = 0;
						int totalprod = 0;
						float montoprod = 0;

						mostrardatospersona(per);

						printf(" EMPRESA: %s \n\n", emp->nombreEmp);

						ped = per->aba;

						for( ; ped; ped=ped->prox ){
							prodinc = ped->aba;

							if (ped->codigoEmp == emp->codigoEmp){
								printf("---------------------------------------------------------------------\n");
								printf("---------------------------------------------------------------------\n\n");
								printf(" NUMERO DE FACTURA: ");
								if (ped->factura<10) printf ("000");
								 else if (ped->factura<100) printf("00");
							   	  else if (ped->factura<1000) printf("0");
								printf("%i - MONTO TOTAL: %.2f$ - FECHA: %i/%i/%i - ENTREGADO: ", ped->factura, ped->monto_total, ped->fechas.dia, ped->fechas.mes, ped->fechas.anio );
								if (ped->entregados) printf("SI\n\n");
								else printf("NO\n\n");
								//imprimir datos de cada factura
								totalped++;
								montoprod += ped->monto_total;

								for (; prodinc; prodinc=prodinc->prox){
										printf("---------------------------------------------------------------------\n\n");
										printf("\t CODIGO DEL PRODUCTO: ");
										if (prodinc->codigoPrt<10) printf ("000");
										 else if (prodinc->codigoPrt<100) printf("00");
									   	  else if (prodinc->codigoPrt<1000) printf("0");
										printf("%i - CANTIDAD: %i - PRECIO: %.2f$ \n\n", prodinc->codigoPrt, prodinc->cantidad, prodinc->precio );
										//imprimir cada detalle de esa factura
										totalprod += prodinc->cantidad;
								}
							}
						}

						if (totalped == 0) {
							printf(" Esta persona no tiene registrada ninguna factura a nombre de la empresa '%s'\n\n", emp->nombreEmp);
							return;
						}
						printf("---------------------------------------------------------------------\n");
						printf("---------------------------------------------------------------------\n\n");
						printf(" TOTAL DE PEDIDOS HECHOS: %i - MONTO TOTAL PEDIDO: %.2f$ - TOTAL DE PRODUCTOS: %i \n\n", totalped, montoprod, totalprod  );

				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que devuleve la direccion de memoria, donde se encuentra el pedido con el monto mas alto*/
				Pedidos *montomasalto(Pedidos *auxped){

					Pedidos *aux=auxped;
					Pedidos *mayor1=NULL;
					int mayor=0;

					for(;aux;aux=aux->prox){
						if(aux->monto_total>mayor){
							mayor=aux->monto_total;
							mayor1=aux;
						}
					}

					return mayor1;
				}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que devuelve la direccion de memoria, donde se encuentra el pedido con la fecha mas reciente*/
						Pedidos *fechamasreciente(Pedidos *auxped){

							Pedidos *aux=auxped;
							Pedidos *reciente=NULL;
							int anio,mes,dia;
							anio=0;
							mes=0;
							dia=0;

							for(;aux;aux=aux->prox){ //Se recorre cada factura buscando la mas reciente
								if(aux->fechas.anio >anio){
									anio=aux->fechas.anio;
									mes=aux->fechas.mes;
									dia=aux->fechas.dia;
									reciente=aux;
								}
								else{
									if (aux->fechas.anio==anio){
										if(aux->fechas.mes>mes){
											anio=aux->fechas.anio;
											mes=aux->fechas.mes;
											dia=aux->fechas.dia;
											reciente=aux;
										}
										else{
											if(aux->fechas.mes==mes){
												if(aux->fechas.dia>= dia){
													anio=aux->fechas.anio;
													mes=aux->fechas.mes;
													dia=aux->fechas.dia;
													reciente=aux;
												}
											}
										}
									}
								}
							}

							return reciente;

						}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Rutina para borrar una lista completa
				void borrarLista(Pedidos **l)
					{
						if(l && *l)
						{
							borrarLista(&((*l)->prox));
							Pedidos *aux = *l;
							*l = NULL;
							delete aux;
						}
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Rutina para mostrar los numeros de las facturas entregadas y ordenarlo por monto total o por fecha de emision
					void mostrarfacturasentregadas(Personas *per,Pedidos **auxped,Empresas *emp){

						Personas *tper=per;
						Pedidos *xped;
						Pedidos *tped;
						int consulta;
						int a=0;
						Pedidos *tped2=*auxped;
						float montototal=0;

						//Se crea una lista auxiliar (auxped) para guardar las facturas entregadas

						for( ;tper;tper=tper->prox){
							tped=tper->aba;
							for(;tped;tped=tped->prox){
								if(tped->entregados){
									xped= new Pedidos;
									xped->factura=tped->factura;
									xped->codigoEmp=tped->codigoEmp;
									xped->fechas.anio=tped->fechas.anio;
									xped->fechas.mes=tped->fechas.mes;
									xped->fechas.dia=tped->fechas.dia;
									xped->entregados=tped->entregados;
									xped->monto_total=tped->monto_total;
									xped->aba=NULL;
									xped->prox=*auxped;
									*auxped=xped;
								}
							}
						}
						if(*auxped==NULL){
							printf("No hay facturas entregadas en el sistema \n");
							return;
						}
							printf(" Mediante que opcion desea ordenarr?\n");
							printf(" 1- Monto total\n 2- Fecha de emision \n ");

							do {
								fflush(stdin);
								introduciropcion(&consulta);
								if (consulta!=1 && consulta!=2) {
								printf("\n Debe ingresar una de las opciones indicadas ");

								}

							} while(consulta!=1 && consulta!=2);

							system("cls");
							switch (consulta){
							//Se ordena por Monto total de mayor a menor
							case 1:
								printf("\n\n\tFACTURAS ENTREGADAS POR MONTO TOTAL \n\n");
								tped2=*auxped;

								for(;tped2;tped2=tped2->prox){
									a++;
									montototal+=tped2->monto_total;
								}

								Pedidos *aux;
								for(int x=0;x<a;x++){
									aux=montomasalto(*auxped);
									if (aux){
										Empresas *em;
										em=buscarempresa(emp,aux->codigoEmp,vacio,0); //Se busca la factura con el monto total mas alto
										printf(" NUMERO DE FACTURA: ");
										if (aux->factura<10) printf ("000");
											else if (aux->factura<100) printf("00");
				   							else if (aux->factura<1000) printf("0");
										printf("%i - EMPRESA: %i - TIPO DE EMPRESA:%i - MONTO TOTAL: %.2f $ - FECHA: %i/%i/%i\n",aux->factura,aux->codigoEmp,em->tipo,aux->monto_total,aux->fechas.dia,aux->fechas.mes,aux->fechas.anio);
										aux->monto_total=0;	//Una vez, impresa la factura, se coloca su monto en 0 para buscar la proxima factura con el monto total mas alto
								}
							}

							break;
							//Se ordena por Fecha de emision la mas reciente primero
							case 2:
								printf("\n\n\tFACTURAS ENTREGADAS POR FECHA DE EMISION \n\n");
								Pedidos *tped1=*auxped;
								a=0;
								montototal=0;
								for(;tped1;tped1=tped1->prox){
									a++;
									montototal+=tped1->monto_total;
								}

								Pedidos *aux1;
								for(int x=0;x<a;x++){
									aux1=fechamasreciente(*auxped);
									if (aux1){
										Empresas *em;
										em=buscarempresa(emp,aux1->codigoEmp,vacio,0); //Se busca la factura con la fecha reciente
										printf(" NUMERO DE FACTURA: ");
										if (aux1->factura<10) printf ("000");
											else if (aux1->factura<100) printf("00");
				   							else if (aux1->factura<1000) printf("0");
										printf("%i - EMPRESA: %i - TIPO DE EMPRESA:%i - MONTO TOTAL: %.2f $ - FECHA: %i/%i/%i\n",aux1->factura,aux1->codigoEmp,em->tipo,aux1->monto_total,aux1->fechas.dia,aux1->fechas.mes,aux1->fechas.anio);
										aux1->fechas.anio=0; //Se actualiza y se coloca la fecha en 0/0/0 para buscar la proxima factura con la fecha mas reciente
										aux1->fechas.mes=0;
										aux1->fechas.dia=0;
									}

								}

								break;
							}

						printf("\n");
						printf("\nTOTAL DE FACTURAS ENTREGADAS: %i - MONTO TOTAL DE FACTURAS ENTREGADAS: %.2f $\n\n",a,montototal);
				 		borrarLista(auxped); //Se borra la lista auxiliar

				 	}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para buscar la persona con la mayor cantidad de productos compradas*/
				Personas *personacantidadmasalta(Personas *tper,int *mayor,int *menor){

						Personas *per=tper;
						Pedidos *tped;
						int mayor2=0;
						int montomayor;
						int montomenor;
						int menor2=0;
						Personas *retorno=NULL;
						bool entregado = false; //Un booleano que pasa a verdadero cuando encuentre una persona con algun pedido entregados
												// de esta manera podemos saber cuando solo queden personas con pedidos no entregados

						for(;per;per=per->prox){
							montomayor=0;
							montomenor=0;

							tped=per->aba;
							for(;tped;tped=tped->prox){
								if(tped->entregados){
									Prodinc *prod=tped->aba;
									for(;prod;prod=prod->prox){
										montomayor+=prod->cantidad;
									}
								}
								else{
									Prodinc *prod=tped->aba;
									for(;prod;prod=prod->prox){
										montomenor+=prod->cantidad;
									}

								}
							}
							if(montomayor>mayor2){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
								entregado = true;
							} else if (!entregado){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
							}
						}

						*mayor=mayor2;
						*menor=menor2;

						return retorno;

					}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para buscar la persona con el mayor monto total de compras realizadas (todos los pedidos entregados)*/
					Personas *personamontomasalto(Personas *tper,float *mayor,float *menor){

						Personas *per=tper;
						Pedidos *tped;
						float mayor2=0;
						float montomayor;
						float montomenor;
						float menor2=0;
						Personas *retorno=NULL;
						bool entregado = false; //Un booleano que pasa a verdadero cuando encuentre una persona con algun pedido entregados
												// de esta manera podemos saber cuando solo queden personas con pedidos no entregados

						for(;per;per=per->prox){
							montomayor=0;
							montomenor=0;

							tped=per->aba;
							for(;tped;tped=tped->prox){
								if(tped->entregados){
									montomayor+=tped->monto_total;
								}
								else{
									montomenor+=tped->monto_total;
								}
							}
							if(montomayor>mayor2){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
								entregado = true;
							} else if (!entregado){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
							}
						}


						*mayor=mayor2;
						*menor=menor2;

						return retorno;

					}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar las personas con mayor monto gastado */
				void mayorpormonto(Personas **auxper, int a){

					float mayor=0;
					float menor=0;
					float montomayor=0;
					float montomenor=0;
					Personas *tper2;

					for(int x=0;x<a;x++){
						tper2=personamontomasalto(*auxper,&mayor,&menor);
						if(tper2){
							printf(" NOMBRE: %s -- CEDULA: %li -- %.2f $  (-%.2f $)\n\n",tper2->nombre_apellido,tper2->cedula,mayor,menor);
							montomayor+=mayor;
							montomenor+=menor;
							Eliminarpersona(auxper, tper2->cedula); // se debe eliminar cada nodo (que se acaba de usar) de la lista
						}
					}

					printf("\n\t | TOTAL: %.2f $ (-%.2f $) | \n\n",montomayor,montomenor);

				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar las personas con la mayor cantidad de productos comprados */
				void mayorporcantidad(Personas **auxper, int a){

					Personas *tper2;
					int mayor=0;
					int menor=0;
					int montomayor=0;
					int montomenor=0;

					for(int x=0;x<a;x++){
						tper2=personacantidadmasalta(*auxper,&mayor,&menor);
						if(tper2){
							printf(" NOMBRE: %s -- CEDULA: %li -- %d  (-%i)\n\n",tper2->nombre_apellido,tper2->cedula,mayor,menor);
							montomayor+=mayor;
							montomenor+=menor;
							Eliminarpersona(auxper, tper2->cedula); // se debe eliminar cada nodo (que se acaba de usar) de la lista
						}
					}
					printf("\n\t | TOTAL DE PRODUCTOS: %i (-%i) | \n\n",montomayor,montomenor);
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar las personas con mayores montos de compras realizadas y mayor cantidad de productos comprados*/
				void mayoresconsultas(Personas *per, int x){

					Personas *auxper = NULL;
					Personas *tper=per;
					Personas *tper1, *tper2;
					Pedidos *auxped=NULL;
					Pedidos *tped;
					Prodinc *tprodinc, *auxprodinc;
					int a=0;

					//Se crea una lista auxiliar (auxper) para guardar todas las personas

					for(;tper;tper=tper->prox){
						auxped=NULL;
						a++;
						//
						tper1 = new Personas;
						strcpy(tper1->nombre_apellido,tper->nombre_apellido);
						tper1->cedula=tper->cedula;
						//
						if(!tper->aba){
							tper1->aba=NULL;
						}else{
							Pedidos *tped2=tper->aba;
							for(;tped2;tped2=tped2->prox){
								auxprodinc=NULL;
								tped=new Pedidos;
									tped->factura=tped2->factura;
									tped->entregados=tped2->entregados;
									tped->monto_total=tped2->monto_total;

										if (!tped2->aba){
											tped->aba=NULL;
										} else {
											Prodinc *prodinc=tped2->aba;
											for (; prodinc; prodinc=prodinc->prox){
												tprodinc = new Prodinc;
												tprodinc->cantidad=prodinc->cantidad;
												tprodinc->prox=auxprodinc;
												auxprodinc=tprodinc;
											}
											tped->aba=auxprodinc;
										}

									tped->prox=auxped;
									auxped=tped;
							}
							tper1->aba=auxped;
						}
						tper1->prox=auxper;
						auxper=tper1;
					}
					//Si x==1 se mostraran las personas con mayores montos de compras realizadas
					if (x==1) mayorpormonto(&auxper, a);
					else mayorporcantidad(&auxper, a);

				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que devuelve la empresa con mayor ingreso logrado*/
				Empresas *empresamayor(int array[],float *ingreso,int a,Personas *per,Empresas *emp){

					float mayor=0;
					int codigo=0;
					Empresas *temp=NULL;
					int y=0;
					for(int x=0; x<a;x++){
						if(totaling(per,array[x], 1)>mayor){
							mayor=totaling(per,array[x], 1);
							codigo=array[x];
							y=x;
						}
					}
					*ingreso=mayor;
					temp=buscarempresa(emp, codigo, vacio, 0);
					array[y]=0;
					return temp;

				}
          /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que devuelve la cantidad de productos en facturas entregadas o no entregadas de una empresa en especifico*/
				int cantidad ( Personas *per, int codigo ,int z)
				//z=1 es la cantidad de productos en facturas entregadas
				//z=2 es la cantidad de productos en facturas no entregadas
				 {

				 	 int vendido = 0;
				 	 int novendido=0;
					 Personas *aux;
				 	  aux = per;

				 	   for (; aux; aux = aux->prox) {

				 	   	  Pedidos *ped;
				 	   	  ped = aux->aba;

							 for (; ped; ped = ped->prox) {

							     if ( ( ped->codigoEmp == codigo ) && ( ped->entregados ) && (z==1) ) {
							      	 Prodinc *prod;
							      	  prod = ped->aba;

							      	   for (; prod; prod = prod->prox ) {
				                              vendido+=prod->cantidad;
										  }
								  }
								  else{
								  	 if ( ( ped->codigoEmp == codigo ) && (!ped->entregados ) && (z==2) ) {
							      	 Prodinc *prod;
							      	  prod = ped->aba;

							      	   for (; prod; prod = prod->prox ) {
				                              novendido+=prod->cantidad;
										  }
								  }

								  }
							 }
						}
				 	if(z==1){
				 		return vendido;
					}
					else{
						return novendido;
					}


				 }
			///////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion que devuelve la empresa con mayor cantidad de productos vendidos*/
			Empresas *empresacantidad(int array[],int y,Personas *per,Empresas *emp,int *cantidadv){
				int  mayor=0;
				int codigo=0;
				Empresas *temp=NULL;
				int z=0;
					for(int x=0; x<y;x++){
						if(cantidad(per,array[x],1)>mayor){
							mayor=cantidad(per,array[x],1);
							codigo=array[x];
							z=x;
						}
					}
					*cantidadv=mayor;
					temp=buscarempresa(emp, codigo, vacio, 0);
					array[z]=0;
					return temp;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina auxiliar para mostrar las empresas con mayores ingresos logrados (4.3.1) y las empresas con mayor cantidad de productos vendidos (4.3.2)*/
				void mayoresempresas(Empresas *emp,Personas *per,int z){
					Empresas *temp=emp;
					int prodentregado = 0;
					int a=0;
					int y=0;
					Empresas *auxemp;
					float ingresototal=0;
					float ingresototalnovendido=0;
					float ingreso=0;
					int cantidadv=0;
					int cantidadno=0;
					int finalvendido=0;
					int finalnovendido=0;
					float montofinal=0;
					for(;temp;temp=temp->prox){
						a++;
					}

					int array[a+1];
					temp=emp;
					for (int x=0; temp; temp=temp->prox, x++) array[x] = temp->codigoEmp;
					y=a;
					if (z==1){ //4.3.1
					for(int x=0; x<a; x++){
						auxemp=empresamayor(array,&ingreso,y,per,emp);
						if(auxemp){
							printf(" | NOMBRE: %s | -- | TIPO: %i | -- | INGRESO: %.2f $ ( - %.2f $) | -- | CANTIDAD: %i | \n \n ",auxemp->nombreEmp,auxemp->tipo,ingreso,(totaling(per,auxemp->codigoEmp,2)),cantidad(per, auxemp->codigoEmp,1));
							ingresototal+=ingreso;
							prodentregado+=cantidad(per, auxemp->codigoEmp,1);
							ingresototalnovendido+=totaling(per,auxemp->codigoEmp,2);
						}
					}
					printf(" \t | TOTAL INGRESO:  %.2f $ (-%.2f $) | -- | CANTIDAD TOTAL: %i | \n\n",ingresototal,ingresototalnovendido,prodentregado);
					}
					else{ //4.3.2
						for(int x=0; x<a; x++){
						auxemp=empresacantidad(array,y,per,emp,&cantidadv);
						if(auxemp){
							printf(" | NOMBRE: %s | -- | TIPO: %i | -- | CANTIDAD: %i ( - %i) | -- | MONTO TOTAL: %.2f $ | \n \n ",auxemp->nombreEmp,auxemp->tipo,cantidadv,cantidad(per,auxemp->codigoEmp,2),totaling(per,auxemp->codigoEmp,1));
							finalvendido+=cantidadv;
							finalnovendido+=cantidad(per,auxemp->codigoEmp,2);
							montofinal+=totaling(per,auxemp->codigoEmp,1);

						}
					}
					printf(" \t | CANTIDAD TOTAL:  %i (- %i) | -- | MONTO TOTAL: %.2f $| \n\n",finalvendido,finalnovendido,montofinal);
					}
				}
