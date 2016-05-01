var express    = require('express');
var http       = require('http');
var socketIO   = require('socket.io');
var serialport = require('serialport');
var five       = require('johnny-five');


var app = express();
var server = http.Server(app);
var io = socketIO(server);


var TLC_CH = 16;


var isSerialConnected = false;


// var json = {
//   memorys: [
//     [
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }]
//     ],
//     [
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }]
//     ],
//     [
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }]
//     ],
//     [
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
//       [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }]
//     ]
//   ]
// };

var json = {
  memorys: [
    [
      [{ tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }, { tempel: 0.0 }],
    ]
  ]
};

// --------------------------------------------------
/**
 * HTTP
 */
app.get('/', function(req, res) {
  res.sendFile(__dirname + '/views/index.html');
});

// --------------------------------------------------
/**
 * SOCKET
 */
io.on('connection', function(socket) {
  console.log('[Socket] connection');

  socket.on('disconnect', function() {
    console.log('[Socket] disconnected');
  });

  socket.on('signal', function(data) {
    var ch = data.ch - 1;

    var unitIndex = ~~(ch / TLC_CH);
    var recordIndex = ~~(ch / 4);
    var columnIndex = ch - ((recordIndex) * 4);

    json.memorys[unitIndex][recordIndex][columnIndex].tempel = data.tempel;

    // console.log(JSON.stringify(json) + '\n');

    if (isSerialConnected) {
      var sendDate = JSON.stringify(json) + '\n';
      serialPort.write(sendDate);
    }
  });
});


server.listen(3000, function() {
  console.log('🌏 listening on | localhost:3000');
});


// --------------------------------------------------
/**
 * Serial
 */
var serialPort = new serialport.SerialPort(
  '/dev/cu.usbmodem1411',
  {
    baudrate: 9600,
    parser: serialport.parsers.readline('\n')
  }
);

serialPort.on('data', function(data) {
  // Arduino からデータを受信する
  console.log('[serialPort] data | ' + data);
  // serialPort.write('Hello Arduino\n');
});

serialPort.on('open', function() {
  console.log('[serialPort] open');

  setTimeout(function() {
    isSerialConnected = true;
  }, 2000);
});




// serialPort.on('data', function(data) {
//   // Arduino からデータを受信する
//   console.log('[serialPort] data\n' + data);
//   serialPort.write('Hello Arduino\n');
// });

// serialPort.on('open', function() {
//   console.log('[serialPort] open');

//   setTimeout(function() {
//     // Node からArduino にデータを送信する
//     // serialPort.write('Hello Arduino');
//   }, 2000);
// });


// serialPort.on('data', function(data) {
//   // Arduino からデータを受信する
//   console.log('[serialPort] data\n' + data);
//   serialPort.write('Hello Arduino\n');
// });




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