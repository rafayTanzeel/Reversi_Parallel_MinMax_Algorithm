var socket = io.connect();

$(document).ready(function(){
    var MAX_TEMPO = 300;
    var MIN_TEMPO = 40;

    var MAX_VOL = 100;
    var MIN_VOL = 0;

    set_input_val_up("#btnTempoAdd","#Tempo",MAX_TEMPO);
    set_input_val_down("#btnTempoSub","#Tempo",MIN_TEMPO);

    set_input_val_up("#btnVolAdd","#Volume",MAX_VOL);
    set_input_val_down("#btnVolSub","#Volume",MIN_VOL);

    $("#btnNone").click(function(){
        sendUDPCommand("None");
    });

    $("#btnR1B").click(function(){
        sendUDPCommand("R1B");
    });

    $("#btnR2B").click(function(){
        sendUDPCommand("R2B");
    });

    $("#btnHH").click(function(){
        sendUDPCommand("Hit_hat");
    });

    $("#btnSN").click(function(){
        sendUDPCommand("Snare");
    });

    $("#btnB").click(function(){
        sendUDPCommand("Base");
    });

    socket.on('commandReply', function(result) {
        $("footer").show();
    });

});


function set_input_val_up(btnId, inputId, MAX_LIMIT){
    $(btnId).click(function(){
        var inputVal=parseInt($(inputId).val());
        if(inputVal+5>MAX_LIMIT){
            inputVal=MAX_LIMIT;
        }
        else{
            inputVal=inputVal+5;
        }
        if(btnId=="#btnTempoAdd"){
            sendUDPCommand("T "+inputVal);
        }
        else{
            sendUDPCommand("V "+inputVal);
        }
        $(inputId).val(inputVal);
    });
}


function set_input_val_down(btnId, inputId, MIN_LIMIT){
    $(btnId).click(function(){
        var inputVal=parseInt($(inputId).val());
        if(inputVal-5<MIN_LIMIT){
            $(inputId).val(MIN_LIMIT);
        }
        else{
            $(inputId).val(inputVal-5);
        }
        if(btnId=="#btnTempoSub"){
            sendUDPCommand("T "+inputVal);
        }
        else{
            sendUDPCommand("V "+inputVal);
        }
    });
}


function sendUDPCommand(message) {
    socket.emit('Host', message);
};
