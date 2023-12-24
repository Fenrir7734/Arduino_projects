import {Component} from '@angular/core';
import {ESP32ClientService} from "./esp32-client.service";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  constructor(private esp32Service: ESP32ClientService) {
  }

  toggleLed() {
    this.esp32Service.toggleLed().subscribe();
  }
}
