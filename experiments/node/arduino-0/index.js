// var num = 1;
// var br = 0x0f;
// console.log((num << 4) | br);


var serialport = require('serialport');
var five = require('johnny-five');

var serialPort = new serialport.SerialPort(
  '/dev/cu.usbmodem1411',
  {
    baudrate: 9600,
    parser: serialport.parsers.readline('\n')
  }
);

serialPort.on('open', function() {
  console.log('[serialPort] open');

  setTimeout(function() {
    // Node からArduino にデータを送信する
    // serialPort.write('Hello Arduino');
  }, 2000);
});


serialPort.on('data', function(data) {
  // Arduino からデータを受信する
  console.log('[serialPort] data\n' + data);
  serialPort.write('Hello Arduino\n');
});




// var board = new five.Board({
//   port: (function() {
//     var port = new SerialPort('/dev/cu.usbmodem1411', {
//       baudrate: 9600,
//       buffersize: 1
//     });
//     return port;
//   })()
// });



// board.on('ready', function() {
//   // Create an Led on pin 13
//   var led = new five.Led(13);
  
//   // Blink every half second
//   led.blink(1000); 

//   // 終了時にLEDを消灯
//   this.on('exit', function() {
//     led.off();
//   });
// });