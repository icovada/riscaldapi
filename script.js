$(function() {
	var tempwid = $('.lcd').width();
	$(".sparkline").sparkline('html', {
		type: 'line',
		width: 600-tempwid,
    	height: '100',
    	fillcolor: undefined,
    	minSpotColor: '#0000ff',
    	maxSpotColor: '#ff0000',
    	spotRadius: 3,
    	normalRangeMin: 19.7,
    	normalRangeMax: 20.3,
    	normalRangeColor: '#00ff00'
    });

    $( "#slider-vertical > span" ).each(function() {
      // read initial values from markup and remove that
      var value = parseInt( $( this ).text(), 10 );
      $( this ).empty().slider({
        value: value,
        range: "min",
        max: 220,
        min: 180,
        animate: true,
        orientation: "vertical"
      });
      $(this).append("<label for=span id='numeri'>"+value/10+"</label>");
    });
});

$(document).ready(function(){
});