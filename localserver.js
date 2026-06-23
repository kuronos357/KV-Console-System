const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 81 });

console.log('WebSocket server started on port 81');

wss.on('connection', (ws) => {
    console.log('Client connected');

    const interval = setInterval(() => {
        const data = {
            bv: (Math.random() * 2 + 23).toFixed(1) * 1,
            bc: (Math.random() * 2 + 3).toFixed(1) * 1,
            mv: (Math.random() * 2 + 22).toFixed(1) * 1,
            mc: (Math.random() * 2 + 15).toFixed(1) * 1,
            speed: (Math.random() * 10 + 20).toFixed(1) * 1,
            temp: (Math.random() * 20 + 30).toFixed(1) * 1
        };
        ws.send(JSON.stringify(data));
    }, 200);

    ws.on('close', () => {
        clearInterval(interval);
        console.log('Client disconnected');
    });
});