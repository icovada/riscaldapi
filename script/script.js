$(function () {
    //Get array for graph
    $.ajax({
        type: 'GET',       
        url: "php/history.php",
        dataType: 'html',
        context: document.body,
        global: false,
        async: false,
        success: function(data) {
            history=data.substring(0, data.length - 2).split(",");
        }
    });

    $(".lcdtxt").text(history[history.length-1]+"°");
    $("#sparkline").sparkline(history, {
        type: 'line',
        width: 600,// - tempwid,
        height: '100',
        fillcolor: undefined,
        minSpotColor: '#0000ff',
        maxSpotColor: '#ff0000',
        spotRadius: 3,
        normalRangeMin: 19.7,
        normalRangeMax: 20.3,
        normalRangeColor: '#00ff00'
    });

    $("td > #slider").each(function () {
        // read initial values from markup and remove that
        var value = parseInt($(this).text(), 10);
        $(this).after("<label id='numeri'>" + (value / 10).toFixed(1) + "</label>");
        $(this).empty().slider({
            value: value,
            max: 220,
            min: 180,
            animate: true,
            orientation: "vertical",
            slide: function( event, ui ) {
        		$(this).parent().find("label").text((ui.value/10).toFixed(1));
      		}
        });
    });
    
    var d =new Date();
    var n = d.getDay()-1;
    if ( n == -1) { n = 6;}

    $( "#accordion" ).accordion({
    	active: n, //giorno della settimana
    	animate: false
    });

    /* Show the page once jQ has loaded */
    $("#loading").remove();
    $("#lcd").removeClass("hidden");
    $("#sparkline").removeClass("hidden");
    $("#accordion").removeClass("hidden");

    $(".ui-slider-handle").each( function() {
        $(this).text($(this).parent().data("time"))
    });
});
