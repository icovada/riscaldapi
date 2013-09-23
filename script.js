$(function () {
    var tempwid = $('.lcd').width();
    $(".sparkline").sparkline('html', {
        type: 'line',
        width: 600 - tempwid,
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
        $(this).after("<label for=span id='numeri'>" + (value / 10).toFixed(1) + "</label>");
        $(this).empty().slider({
            value: value,
            max: 220,
            min: 180,
            animate: true,
            orientation: "vertical",
            slide: function (event, ui) {
                $(this).parent().find("label").text((parseInt($(this).slider('value'))/10).toFixed(1));
            }
        });
    });
});