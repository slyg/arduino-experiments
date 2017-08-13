const SerialPort = require('serialport');
const parsers = SerialPort.parsers;

const port = new SerialPort('/dev/tty.usbmodem1411', { baudRate: 9600 });
const parser = new parsers.Readline({ delimiter: '\n' });

port
  .pipe(parser)
  .on('open', () => console.log('Port open'))
;

parser
  .on('data', console.log)
;
