import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { InicioComponent } from './inicio/inicio.component';
import { AcercaComponent } from './acerca/acerca.component';
import { ContactoComponent } from './contacto/contacto.component';

import { Routes, RouterModule } from '@angular/router';

const rutas : Routes = [
  {path: 'inicio', component: InicioComponent },
  {path: 'acerca', component: AcercaComponent },
  {path: 'contacto', component: ContactoComponent },
];

@NgModule({
  declarations: [],
  imports: [
    CommonModule, RouterModule.forRoot(rutas)
  ],
  exports: [RouterModule]
})
export class AppRoutingModule { }
