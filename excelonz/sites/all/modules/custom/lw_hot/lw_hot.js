var time_left;
var cinterval;
jQuery(document).ready(function(){

  startinitial();
  hot_submit ();

});

function startinitial() {
  time_left = 20;
  clearInterval(cinterval);
  cinterval = setInterval('starttime()', 1000);
  hots_submit_action ();
  hots_reset_btn();

}

function starttime() {

  sec = Math.round(time_left % 60);
  sec = ("0" + sec).slice(-2);
  document.getElementById('hot_timer').innerHTML = sec;
  time_left--;

  if(time_left == -1){
    clearInterval(cinterval);
    //jQuery('.hot_answer').show();
    jQuery('.desc_wrap.hot .btn-wrap').show();
  }

}

function hots_submit_action () {
  jQuery('#hot-form button#submit-button').live('click',function() {
    jQuery('.hot_answer').show();
    jQuery('#hot-form #edit-next').show();
    jQuery('#hot-form .btn-wrap').hide();
  });
}

function hots_reset_btn () {
  jQuery('#hot-form button#reset').live('click',function() {
    jQuery('#hot-form .sure').text('');
    jQuery('#hot-form .sure').append('Ready <br/> Now ?');
  });
}

function hot_submit (){
  jQuery('.brainteasers.page-hot #edit-finish').click(function () {
    var r = confirm('Are you sure, you want to finish this session ?')
    if (r == true) {
      return true;
     }
     else {
        return false;
     }
  });
}

