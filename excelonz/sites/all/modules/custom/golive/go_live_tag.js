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

time_left = 0;

jQuery(document).ready(function(){
  jQuery('#golive-form #submit-button').removeAttr("disabled");
  jQuery('.user_online:first').addClass('org');
  // Show join/start button based on remaining time to go live session
  /*var a = Drupal.settings.golive_rem_time.rem_time;
  var rem_ms = a*1000;
  if (rem_ms >= 0) {
	  setTimeout(function(){
		//alert('now');
		jQuery('#join-button').removeAttr('disabled');
		jQuery('.session_button').removeAttr('disabled');
	  },rem_ms);
  }
  var secs = parseInt(a,10);
  var hours = Math.floor(secs / (60 * 60));
  var divisor_for_minutes = secs % (60 * 60);
  var minutes = Math.floor(divisor_for_minutes / 60);
  var divisor_for_seconds = divisor_for_minutes % 60;
  var seconds = Math.ceil(divisor_for_seconds);
	if( rem_ms >= 0){
		jQuery('#remain_id').append("Remaining Time : "+hours+":"+minutes+":"+seconds+" Sec");
	}
	*/

time_left = parseInt(Drupal.settings.golive_time.holdtime);
//alert(time_left);
 gtime = time_left*1000;
 jQuery('#option-list').css('opacity','.2');
 jQuery('#option-list').attr('disabled','disabled');
 jQuery('#option-list *').attr('disabled','disabled');

    if ( time_left > 0 ) {
      holdstart();
      setTimeout(function() {
        hold_msg();
      }, gtime);
    }
    else {
     defaultstart();
    }
});

//JS for Remaining Session Timer

var time_left;
var cinterval;
var timestatus=1;

function time_dec(){

  time_left--;

  if(time_left > 60 )
          {min = time_left / 60;
            //min = ("0" + min).slice(-2);
          }
          else {min = 00;}
  sec = Math.round(time_left % 60);
  sec = ("0" + sec).slice(-2);


  document.getElementById('countdown').innerHTML = Math.floor(min) + ':' + sec;
  if(time_left == 0){
    clearInterval(cinterval);

    var l = window.location;
    var base_url = l.protocol + "//" + l.host + "/" + l.pathname.split('/')[0];

    var url_red = base_url + "golive/result/" + l.pathname.split('/')[3];
  	window.location.href = url_red;
  }
}

function defaultstart(){

 jQuery('.hold').remove();
  jQuery('#option-list').css('opacity','1');
  jQuery('#option-list').removeAttr("disabled");
  jQuery('#option-list *').removeAttr("disabled");


  time_left = Drupal.settings.golive_time.duration;
  //time_left = 5;
  clearInterval(cinterval);
  cinterval = setInterval('time_dec()', 1000);
}


function holdstart(){
  time_left = Drupal.settings.golive_time.holdtime;
  //alert("hold start" + time_left);
  clearInterval(cinterval);
  cinterval = setInterval('hold_dec()', 1000);

}

function hold_dec(){
  time_left--;
  if(time_left > 60 ) {
    min = time_left / 60;
    //min = ("0" + min).slice(-2);
  }
  else {
    min = 0;
  }
  sec = Math.round(time_left % 60);
  sec = ("0" + sec).slice(-2);
  document.getElementById('countdown').innerHTML = Math.floor(min) + ':' + sec;
  if(time_left == 0){
    defaultstart();
  }
}

function hold_msg() {

var hold_left = parseInt(Drupal.settings.golive_time.holdtime);
if(hold_left = 0) {
  jQuery('.hold').remove();
  jQuery('#option-list').css('opacity','1');
  jQuery('#option-list').removeAttr("disabled");
  jQuery('#option-list *').removeAttr("disabled");
  return true;
}
  jQuery('.hold').remove();
  if (jQuery('.hold').is(':visible')){
    jQuery('#option-list').css('opacity','.2');
    jQuery('#option-list').attr('disabled','disabled');
    jQuery('#option-list *').attr('disabled','disabled');
  }
  else{
    jQuery('#option-list').css('opacity','1');
    jQuery('#option-list').removeAttr("disabled");
    jQuery('#option-list *').removeAttr("disabled");
  }
}







