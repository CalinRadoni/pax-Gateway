
var gwURL = `ws://${window.location.hostname}/ws`;
var websocket;

window.addEventListener('load', onLoad);

function onLoad(event) {
    wsConnect();
    initButtons();
}

function wsConnect() {
    websocket = new WebSocket(gwURL);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('ws connection opened');
}

function onClose(event) {
    console.log('ws connection closed');
    setTimeout(wsConnect, 2000);
}

function onMessage(event) {
    console.log(`received message from ${event.origin}`);
    console.log(event.data);
    var jsonData = JSON.parse(event.data);
    Object.keys(jsonData).forEach((key) => {
        console.log(key);
        let val = jsonData[key];
        console.log(val);
        switch(key) {
            case "abc":
                break;
            case "defgh":
                break;
        }
    })
}

function initButtons() {
    document.getElementById('btnTestA').addEventListener('click', onClickBtnA);
    document.getElementById('btnTestB').addEventListener('click', onClickBtnB);
}

function onClickBtnA(event) {
    let str = JSON.stringify({'action':'btnA'});
    console.log(str);
    websocket.send(str);
}

function onClickBtnB(event) {
    let arr = [];
    for (let i = 0; i < 500; ++i) {
        arr.push({v: i});
    }
    let str = JSON.stringify(arr);
    console.log(str);
    websocket.send(str);
}
