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
});

$(function() {
    $( "#slider-vertical" ).slider({
      orientation: "vertical",
      range: "min",
      min: 0,
      max: 100,
      value: 60,
    });
});

$(document).ready(function(){
});