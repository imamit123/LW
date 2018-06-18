/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.

 */

 (function ($) {
    Drupal.behaviors.assessments = {
        attach: function (context, settings) {
    jQuery('#golive-form #submit-button').removeAttr("disabled");
    }
  }
}) (jQuery);


jQuery(document).ready(function(){
 /* jQuery('#golive-form #submit-button').removeAttr("disabled");
  var time_left = Drupal.settings.golive_rem_time.rem_time;
  var rem_ms = time_left*1000;
  jQuery('#join-button').hide();
  jQuery('.join_txt').show();
  if (rem_ms >= 0) {

	  setTimeout(function(){
	  jQuery('#join-button').show();
	  jQuery('.join_txt').hide();
		jQuery('.session_button').removeAttr('disabled');
	  },rem_ms);
  }
  jQuery('#golive-form #submit-button').live('click',function () {
		jQuery('#golive-form #edit-next').show();
	});

	//defaultstart();
  */
  jQuery(".dropbox-is-empty td").text("Await your selection");
  var count = 1;
  $("#field-user-status-values tbody tr").each(function( index ) {
    jQuery(this).find('label').text("Friend " + count);
    count++;
  });


});

//JS for Remaining Session Timer
/*
var time_left;
var cinterval;
var timestatus=1;
var min;

function time_dec(){
  time_left--;


  if(time_left > 60 )
          {min = time_left / 60;}
          else {min = 0;}
        sec = Math.round(time_left % 60);


  document.getElementById('countdown').innerHTML = Math.floor(min) + ':' + sec;
  if(time_left == 0){
    clearInterval(cinterval);
  }
}

function defaultstart(){
  time_left = Drupal.settings.golive_rem_time.rem_time;
  //time_left = 5;
  clearInterval(cinterval);
  cinterval = setInterval('time_dec()', 1000);
}

*/


