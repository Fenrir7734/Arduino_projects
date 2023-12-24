import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";

@Injectable({
  providedIn: 'root'
})
export class ESP32ClientService {
  private readonly url = 'http://192.168.1.2'

  constructor(private http: HttpClient) { }

  toggleLed(): Observable<any> {
    return this.http.get(`${this.url}/led`);
  }
}
