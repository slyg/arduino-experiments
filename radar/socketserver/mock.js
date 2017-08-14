const WebSocket = require('ws')

const wss = new WebSocket.Server({ port: 9999 })

function* gen() {
  let angle = 0
  while (angle <= 180) {
    yield { angle, distance: Math.floor(Math.random() * 30) }
    angle++
  }
  yield* gen()
}

wss.on('connection', function connection(ws) {

  const data = gen()

  const id = setInterval(() => {
    ws.send(JSON.stringify(data.next().value))
  }, 20)

  ws.on('close', () => {
    clearInterval(id)
  })

})
