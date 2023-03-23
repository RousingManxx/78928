import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class DataService {
	constructor (private http: HttpClient){}
	
	//definir metodo SALVAR
	salvar(saludador:String[]){
		this.http.post<any>('https://chunchero-88ce4-default-rtdb.firebaseio.com/saludador.json', saludador)
		.subscribe(
			response => console.log ( 'respuesta '+response),
			error => console.log ( 'error '+error)
		);
	}
}
