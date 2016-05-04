
var co = require('co');
var SerialPort = require('serialport').SerialPort;
var five = require('johnny-five');


/**
 * sleep
 */
function sleep(ms) {
  return function (cb) {
    setTimeout(cb, ms);
  };
}



var board = new five.Board({
  port: new SerialPort('/dev/cu.usbmodem1411', {
    baudrate: 57600
  })
});


board.on('ready', function() {
  this.pinMode(4, five.Pin.OUTPUT);
  this.pinMode(5, five.Pin.OUTPUT);
  this.pinMode(6, five.Pin.PWM);
  this.pinMode(13, five.Pin.OUTPUT);


  this.digitalWrite(13, 1);

  this.digitalWrite(4, 0);
  this.digitalWrite(5, 1);
  this.analogWrite(6, 255);



  // this.loop(20, (function (_this) {
  //   var counter = 0;

  //   return function() {
  //     var sin = Math.sin(counter * Math.PI / 180.0);
  //     var isHot = sin >= 0 ? true : false;

  //     _this.digitalWrite(4, 0);
  //     _this.digitalWrite(5, 1);
  //     _this.analogWrite(6, 255);

  //     counter++;
  //   };
  // })(this));

  // 終了時にLEDを消灯
  this.on('exit', () => {
    this.digitalWrite(13, 0);
  });
})