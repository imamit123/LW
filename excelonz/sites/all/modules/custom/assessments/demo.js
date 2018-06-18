/*jQuery(function($) {

	// ********************
	//$('.qwerty:first').keyboard({ layout: 'qwerty' });

	// QWERTY Password
	// ********************
	$('.qwerty:eq(1)').keyboard({
		openOn   : null,
		stayOpen : true,
		layout   : 'qwerty'
	});
	$('.qwerty').click(function(){
		$('.qwerty:eq(1)').getkeyboard().reveal();
	});
	// since IE adds an overlay behind the input to prevent clicking in other inputs (the keyboard may not automatically open on focus... silly IE bug)
	// We can remove the overlay (transparent) if desired using this code:
	$('.qwerty:eq(1)').bind('visible.keyboard', function(e, keyboard, el){
	 $('.ui-keyboard-overlay').remove(); // remove overlay because clicking on it will close the keyboard... we set "openOn" to null to prevent closing.
	});

	// QWERTY Text Area
	// ********************
	$('.qwerty:last').keyboard({
		layout   : 'qwerty',
		lockInput: false // prevent manual keyboard entry
	});

}); (jQuery);*/

(function ($) {
    Drupal.behaviors.assessments = {
        attach: function (context, settings) { 
	// ********************
	reset();
		fib_buttons ();	
	userkeypress();
	submit_action ();
	$('#edit-next').css('display','none');
	jQuery('.ans_d').css('display','none');
	jQuery('.desc p').css('display','none');
	$('.keyarea #fib_expected').click(function () {
		$('#submit-button').removeAttr('disabled');
	});
	$('div.ui-keyboard *').click(function () {
		$('#submit-button').removeAttr('disabled');
	});
	$('.ui-keyboard  textarea.qwerty').keypress(function(){
	    $('#submit-button').removeAttr('disabled');
	});
/*
	jQuery(function($) {

	// ********************
	//$('.qwerty:first').keyboard({ layout: 'qwerty' });

	// QWERTY Password
	// ********************
	$('.qwerty:eq(1)').keyboard({
		openOn   : null,
		stayOpen : true,
		layout   : 'qwerty'
	});
	$('.qwerty').click(function(){
		$('.qwerty:eq(1)').getkeyboard().reveal();
	});
	// since IE adds an overlay behind the input to prevent clicking in other inputs (the keyboard may not automatically open on focus... silly IE bug)
	// We can remove the overlay (transparent) if desired using this code:
	$('.qwerty:eq(1)').bind('visible.keyboard', function(e, keyboard, el){
	 $('.ui-keyboard-overlay').remove(); // remove overlay because clicking on it will close the keyboard... we set "openOn" to null to prevent closing.
	});

	// QWERTY Text Area
	// ********************
	$('.qwerty:last').keyboard({
		layout   : 'qwerty',
		lockInput: false // prevent manual keyboard entry
	});

	}); (jQuery);*/
	}
  }
}) (jQuery);


jQuery(document).ready(function(){
	reset();
	fib_buttons ();		
	submit_action ();
});


function reset () {
	jQuery('.btn-wrap-inner button#reset').live('click',function() {
		jQuery( '.give_val' ).empty();
		jQuery( '.keyarea .give_val' ).val('');
		jQuery('.btn-wrap-inner p').hide();
		jQuery('.btn-wrap-inner #reset').hide();
		jQuery('.btn-wrap-inner #submit-button').hide();
	});
}

function submit_action () {
	jQuery('.btn-wrap-inner button#submit-button').live('click',function() {
		var a = jQuery('.mrgval').text().toLowerCase().trim();
	var c = jQuery('#fib_correct').val().toLowerCase().trim();
	if ( a == c ) {
		jQuery('#fib_expected').css({'background':'green','color':'#fff'});
		jQuery('.fib_area').empty();
		jQuery('.fib_area').append(c);
		jQuery('.keyarea #fib.give_val').append('Correct');
	}else{
		jQuery('#fib_expected').css({'background':'red','color':'#fff'});
		jQuery('.fib_area').empty();
		jQuery('.fib_area').append(c);
		jQuery('.keyarea #fib.give_val').append('Wrong');
	}
	jQuery('.userenter').attr('disabled','disabled');
	jQuery('.fib .btn-wrap-inner').hide();
		jQuery('.desc_wrap .descs').show();
		jQuery('.desc_wrap .descs p').show();
		jQuery('.desc_wrap p').click(function() {
			jQuery('.desc_wrap .descs .ans_desc').show();
		});
		jQuery('#edit-next').show();
	});
}

// Fill in the blank question
function userkeypress() {
	jQuery('.userenter').keyup(function(e){
		if(jQuery(this).val().length==jQuery(this).attr('maxlength')) {
			jQuery(this).next(':input').focus();
		}
		var txtData = [];
		jQuery('.userenter').each(function () {
			 txtData.push(jQuery(this).val());
		});
		jQuery(".mergeval").val(txtData.join(''));
		jQuery('.mergeval').html(jQuery(".mergeval").val());
    e.preventDefault();
	});
	
}

function fib_buttons () {
	var count_input = jQuery('#fib_expected input').size();
	var yesornos = 0;
	jQuery('.userenter').each(function(){
		var value = jQuery(this).val();
		if(value != '') {
				yesornos++;
		}
	});
	if(yesornos == count_input) {
		var btn_html = jQuery('.btn-wrap').html();
		jQuery('.desc_wrap').append(btn_html);
			jQuery('.fib .btn-wrap-inner,.fib .btn-wrap-inner p,.fib .btn-wrap-inner button').show();
		}
}

function fib_check () {
	var a = jQuery('.mrgval').text().toLowerCase().trim();
	var c = jQuery('#fib_correct').val().toLowerCase().trim();
	if ( a == c ) {
		jQuery('#fib_expected').css({'background':'green','color':'#fff'});
		jQuery('.fib_area').empty();
		jQuery('.fib_area').append(c);
		jQuery('.keyarea #fib.give_val').append('Correct');
	}else{
		jQuery('#fib_expected').css({'background':'red','color':'#fff'});
		jQuery('.fib_area').empty();
		jQuery('.fib_area').append(c);
		jQuery('.keyarea #fib.give_val').append('Wrong');
	}
	jQuery('.userenter').attr('disabled','disabled');
	jQuery('.fib .btn-wrap-inner').hide();
}



