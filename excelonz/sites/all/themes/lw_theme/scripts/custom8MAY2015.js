jQuery(window).load(function(){
var l = window.location;
var base_url = l.protocol + "//" + l.host + "/" + l.pathname.split('/')[0];
//base_url = Drupal.settings.base_path;
var base_url2 = l.pathname.split('/')[4];
jQuery('.subject').find("#" + base_url2).prev().addClass('active');
jQuery('.subject').find("#" + base_url2).css('display','block')
    tdiv = 0;
jQuery('.button-option.mcq .input_class').each(function () {
hdiv = jQuery(this).height();
if(hdiv > tdiv) {
// tdiv = tdiv + 11;
tdiv = hdiv;
}
});
tdiv = tdiv + 11;
jQuery('.button-option.mcq .input_class').height(tdiv)
if(jQuery('#downloadify').length > 0) {
    Downloadify.create('downloadify', {
filename: function(){
var d = new Date();
var strDate = d.getFullYear() + "_" + (d.getMonth()+1) + "_" + d.getDate();
return 'Report for '+strDate+'.xls';
},
data: function(){
return jQuery('#table_export').html();
},
swf: base_url +'/sites/all/themes/lw_theme/scripts/media/downloadify.swf',
downloadImage: base_url + '/sites/all/themes/lw_theme/scripts/images/download.png',
width: 100,
height: 30,
transparent: true,
append: false
});
 }
});


(function ($) {
    Drupal.behaviors.custom = {
        attach: function (context, settings) {
btn_html = jQuery('.btn-wrap ').html();
//jQuery('.desc_wrap').append('<div class="btn-wrap">'+btn_html+'</div>');

if(jQuery('.desc_wrap .btn-wrap').length == 0) {
 jQuery('.desc_wrap').append('<div class="btn-wrap">'+btn_html+'</div>');
}
a = jQuery('#assessments-form .assessment-header .oness').last().text();
var contains = a.indexOf("OOPS");
if(contains == 0){
jQuery('.desc_wrap').addClass('sad');
jQuery('.desc_wrap').removeClass('nactive');
}
var contains_b = a.indexOf("Congrats");
if(contains_b == 0){
jQuery('.desc_wrap').addClass('nactive');
jQuery('.desc_wrap').removeClass('sad');
}
var contains_c = a.indexOf("OOPS you are back to Level0");
if(contains_c == 0){
jQuery('.testdiv').remove();
}
}
  }
}) (jQuery);

jQuery(document).ready(function(){
jQuery('.chooseasubscriptionpackage #block-block-19').hide();

// js for teacher assignment text field total value by deepak
    jQuery( "#generate-assignment-code-form .form-type-textfield" ).change(function() {
        var very_easy = jQuery("#generate-assignment-code-form .form-type-textfield #very_easy_textbox").val();
        var easy = jQuery("#generate-assignment-code-form .form-type-textfield #edit-easy").val();
        var difficult = jQuery("#generate-assignment-code-form .form-type-textfield #edit-difficult").val();
        var very_difficult = jQuery("#generate-assignment-code-form .form-type-textfield #edit-very-difficult").val();
        var total = (+very_easy + +easy + +difficult + +very_difficult);
        jQuery('#edit-total').val(total);
        var final_total = jQuery('#edit-total').val();


        //alert(product_offer_price);
        //alert(product_price);
        if(final_total > 20 )
        {
            //alert("You can Select a Maximum of 20 question per assignment");
            jQuery('#generate-assignment-code-form .form-submit').attr('disabled','disabled').addClass('disabled');
            jQuery('#error_msg').text('You can Select a Maximum of 20 question per assignment').show();
        }
        if(final_total <= 20 )
        {
            //alert("You can Select a Maximum of 20 question per assignment");
            jQuery('#generate-assignment-code-form .form-submit').removeAttr("disabled").removeClass('disabled');
            jQuery('#error_msg').text('You can Select a Maximum of 20 question per assignment').hide();

        }
    });
// js for parent assignment text field total value by deepak
    jQuery( "#generate-parent-assignment-code-form .form-type-textfield" ).change(function() {
        var very_easy = jQuery("#generate-parent-assignment-code-form .form-type-textfield #very_easy_textbox").val();
        var easy = jQuery("#generate-parent-assignment-code-form .form-type-textfield #edit-easy").val();
        var difficult = jQuery("#generate-parent-assignment-code-form .form-type-textfield #edit-difficult").val();
        var very_difficult = jQuery("#generate-parent-assignment-code-form .form-type-textfield #edit-very-difficult").val();
        var total = (+very_easy + +easy + +difficult + +very_difficult);
        jQuery('#edit-total').val(total);
        var final_total = jQuery('#edit-total').val();


        //alert(product_offer_price);
        //alert(product_price);
        if(final_total > 20 )
        {
            //alert("You can Select a Maximum of 20 question per assignment");
            jQuery('#generate-parent-assignment-code-form .form-submit').attr('disabled','disabled').addClass('disabled');
            jQuery('#error_msg').text('You can Select a Maximum of 20 question per assignment');
        }
        if(final_total <= 20 )
        {
            //alert("You can Select a Maximum of 20 question per assignment");
            jQuery('#generate-parent-assignment-code-form .form-submit').removeAttr("disabled").removeClass('disabled');

        }
    });


    jQuery("table.teacher_assignment.no-level-table tr td.mcq-image").find("img").parent().parent().addClass("mcq-image-exist");

  /*
    subscription static page js
   */
  //jQuery("#subscription-static-get-form input:radio").attr('disabled',true);
/*
  $("#subscription-static-get-form .form-type-checkbox input:not(:checked)").each (function () {
    var nid = $(this).val();
    var class_nm = ".form-item-duration-" + nid;

    var c = jQuery(".other-wrapper").find('input[.form-radio][value=0]');
    jQuery(class_nm +" input:radio").attr('disabled',true);

  });
*/
//static page js
  //$("#subscription-static-get-form .form-type-radios input:checked").attr('class', 'radio-chk');
  //var gk_chk1 = jQuery(".radio-chk").not('#edit-duration-4-7').length;
  /*if(gk_chk1 > 1) {
  jQuery('#edit-duration-4-7').attr('checked', 'checked');
    jQuery('#edit-duration-4-7').addClass('radio-chk');
    jQuery('#edit-duration-4-7').after('<span class="freespan" style= "padding-left:10px;" >Complimentary</span>').show();
  }
  */
  var checked = $("#subscription-static-get-form .form-type-checkbox input:checked").length > 0;
  if(checked) {
    jQuery('#edit-add-to-cart').val('Update Cart');
  }


//subscription page
//$(".chooseasubscriptionpackage .form-type-radios input:checked").attr('class', 'radio-chk');
//$(".chooseasubscriptionpackage").find('input[.form-radio][value=0]').removeClass('radio-chk');
//$(".chooseasubscriptionpackage .form-type-radios input").last().attr('class', 'gk-radio');
/*var gk_chk1 = jQuery(".radio-chk").not('.gk-radio').length;
  if(gk_chk1 > 1) {
  jQuery('.gk-radio').attr('checked', 'checked');
    jQuery('.gk-radio').addClass('radio-chk');
    jQuery('.gk-radio').after('<span class="freespan" style= "padding-left:10px;">Complimentary</span>').show();
  }
*/
  var checked = $("#subscription-static-get-form .form-type-checkbox input:checked").length > 0;
  if(checked) {
    jQuery('#edit-add-to-cart').val('Update Cart');
  }




/*
    $("#subscription-static-get-form .form-type-checkbox input:checkbox").click( function(){
      var nid = $(this).val();

      var class_nm = ".form-item-duration-" + nid;

      if( $(this).is(':checked') ){
        jQuery(class_nm +" input:radio").attr('disabled',false);
      }
      else {
        var c = jQuery(".other-wrapper").find('input[.form-radio][value=0]');

        //J2R: CHANGED
        //jQuery(c).attr('checked', false);

        jQuery(class_nm +" input:radio").prop('checked', false);
        jQuery(class_nm +" input:radio").attr('disabled',true);

      }
    });
*/
  /*
  OVER subscription status page js
   */


  //alert('test');
$("#block-menu-menu-social-media a").attr("target","_blank");

jQuery('.testdiv').remove();
subject_term_load();
subject_open_url();
free_subscription ();

if (jQuery('#edit-field-go-live-subject').length > 0){
golive_multistep ();
}
$("#myTable").tablesorter( {sortList: [[0,0], [1,0]]} );
$("#assignment_sort").tablesorter( {sortList: [[0,0], [1,0]]} );

if(jQuery('.page-report-performance-teacher').length>0 || jQuery('.page-report-teacher-student').length>0 || jQuery('.page-teacher-topic-report').length>0 || jQuery('.page-report-teacher').length>0) {
jQuery('#print').click( function () {
var element_to_print = "table_export";
PrintDiv(element_to_print);
});
};
if(jQuery('.page-teacher-topic-progress').length>0){
jQuery('.page-teacher-topic-progress #print').click( function () {
var element_to_print = "block-system-main";
PrintDiv(element_to_print);
});
};
/*if (jQuery('.page-teacher-topic-progress').length > 0 && jQuery('#print').length > 0){
alert("shashp");
var element_to_print = "block-system-main";
jQuery('#print').click( function () {
PrintDiv(element_to_print);
});*/


/*total_width = jQuery('#question_area').width();
q_t = total_width - aggr_width;
q_t_1 = q_t - 2;
jQuery('.queston_img').css('width',aggr_width);
jQuery('.question-text').css('width',q_t_1)*/
//jQuery('.queston_img').width(aggr_width);

jQuery('.input_wrapper1 .form-submit').click(function () {
    jQuery(this).parent().hide();
});
  jQuery('.notify_acc_rej').hide();
jQuery('.count_notify').toggle(
function(){
jQuery('.notify_acc_rej').slideDown('slow');
},
function(){
jQuery('.notify_acc_rej').slideUp('slow');
}
);
jQuery('#golive-form #submit-button').live('click',function () {
jQuery('#golive-form #edit-next').show();
});

jQuery('.user_detail .user_menu ').hide();
jQuery('.user_detail span.name').toggle(
function(){
jQuery('.user_detail .user_menu ').slideDown('slow');
},
function(){
jQuery('.user_detail .user_menu ').slideUp('slow');
}
);
jQuery(document).click(function() {
    if ($('.user_menu, .notify_acc_rej').is(':visible'))
        $('.user_menu, .notify_acc_rej').slideUp();
});


        // Accept and Reject
        jQuery('#golive-acc-rej').submit(function () {
            return false;
        });

        jQuery('#golive-acc-rej input').click(function(){

          var count = parseInt(jQuery('.notify_num').text());
count = count-1;
jQuery('.notify_num').text(count);

            jQuery('#golive-acc-rej input').type = 'button';
            var input_val = jQuery(this).val();
            var input_nid = jQuery(this).attr('name');
            jQuery.ajax({
               url:Drupal.settings.basePath +"notification_save",
               data:{status:input_val,nid:input_nid}
            });
            jQuery(this).parent().hide();
            jQuery(this).parent().parent().append('<p class="txt_wrap" style="color: #FFFFFF;font-size: 20px;padding-top: 10px;text-align: center;">Status Update</p>');
setTimeout("jQuery('p.txt_wrap').hide()", 2000);
        });

        //accept and reject page
jQuery('#golive-acc-rej-pg').submit(function () {
            return false;
        });
        jQuery('#golive-acc-rej-pg input').click(function(){
            jQuery('#golive-acc-rej-pg input').type = 'button';
            var input_val = jQuery(this).val();
            var input_nid = jQuery(this).attr('name');
            jQuery.ajax({
               url:Drupal.settings.basePath +"notification_save",
               data:{status:input_val,nid:input_nid}
            });
            jQuery(this).parent().hide();
            jQuery(this).parent().parent().append('<p class="txt_wrap" style="color: #FFFFFF;font-size: 20px;padding-top: 10px;text-align: center;">Status Update</p>');
setTimeout("jQuery('p.txt_wrap').hide()", 2000);
        });
});

(function ($) {
    Drupal.behaviors.assessments = {
        attach: function (context, settings) {
golive_mcq_submit ();
golive_tf_submit ();
golive_fib_submit ();
hide_next ();
//grab_val ();
jQuery('.ans_d').css('display','none');
jQuery('.desc p').css('display','none');
jQuery('.desc p').click(function() {
jQuery('.ans_d').slideDown('slow');
});
//jQuery('.page-admin-people-p2rp-create .field-name-field-class-user .selects option').removeClass('has-children').addClass('has-no-children');
     }
  }
}) (jQuery);

jQuery(document).ready(function(){
  jQuery('.disablebutton input').prop('disabled', true);
  jQuery('.page-user-edit.role-student #tasks ul li:first-child a').html("Login & Profile Details");
  jQuery('.page-user-edit.role-student #tasks ul li:last-child a').html("School & Interests");

  jQuery(".form-item-profile-student-field-childs-email-und-0-email label").html("Child's Email <i>(if available)</i>");
    //jQuery('.page-admin-people-p2rp-create-student .selects option').removeClass('has-children').addClass('has-no-children');
//jQuery('.page-admin-people-p2rp-create-student .edit-profile-student-field-subjects option')
jQuery('#user-register-form .form-item-roles-change-5 #edit-roles-change-5').attr('checked', true);
jQuery('#user-register-form .form-item-roles-change-5 #edit-roles-change-5').attr('disabled', true);
jQuery('#user-register-form .form-item-roles-change').hide();
//jQuery('.page-admin-people-p2rp-create-student .selects option').removeClass('has-children').addClass('has-no-children');
jQuery('#submit-button').click(function() {
jQuery('.button-option input').click(function() {
//alert('clicked');
var a = jQuery(this).attr('id');
jQuery('.give_val').append(a);
});
jQuery('#golive-form .mcq .radio-option input#Correct').parent().css({'background':'green','color':'#fff'});
var textarea_val = jQuery('.give_val').text();
if (textarea_val == 'Wrong'){
jQuery('.desc p').css('display','block');
}

    jQuery('.radio-option input').attr('disabled','true');
jQuery('#edit-next').show();
jQuery('.tsq-next-callback').show();

//jQuery('.button-option #Correct').css({'background':'green','color':'#fff'});
golive_fib_check ();
});

jQuery('#edit-next').click(function() {
jQuery('#reset').attr('disabled','false');
$('.button-option input').click(function() {
var a = $(this).attr('id');
$('.give_val').append(a);
});
});

golive_fib_check ();
});


function hide_next () {
   jQuery('#edit-next').hide();
   jQuery('.tsq-next-callback').hide();
}


function golive_mcq_submit () {

//jQuery('#golive-form #submit-button').attr('disabled','disabled');
jQuery('#golive-form .radio-option input').click ( function () {
jQuery('#submit-button').removeAttr('disabled');
jQuery('#golive-form .give_val').empty();
//alert('Test this');
var mcq_click = jQuery(this).attr('id');
//alert(mcq_click);
jQuery('#golive-form .give_val').text(mcq_click);
});
}

function golive_tf_submit () {
//jQuery('#golive-form #submit-button').attr('disabled','disabled');
jQuery('#golive-form .tf_questions input').click ( function () {
jQuery('#submit-button').removeAttr('disabled');
jQuery('#golive-form .tf_questions input').attr('disabled','disabled');
var tf_click = jQuery(this).attr('id');
//alert(mcq_click);
jQuery('#golive-form .give_val').text(tf_click);
});
}

function golive_fib_submit () {
//jQuery('#golive-form #submit-button').attr('disabled','disabled');
jQuery('#golive-form #fib_expected_bt').click ( function () {
jQuery('#submit-button').removeAttr('disabled');
});
}

function golive_fib_check () {
// Go live fib form
if (golive_fib_correct_bt) {
var golive_fib_correct_bt = jQuery('#golive-form #fib_correct_bt').val().toLowerCase();
var golive_fib_expected_bt = jQuery('#golive-form #fib_expected_bt').val().toLowerCase();
if( golive_fib_correct_bt != golive_fib_expected_bt ){
jQuery('#golive-form .fib #fib_expected_bt').css({'background':'red','color':'#fff'});
jQuery('#golive-form .fib #fib_correct_bt').empty();
jQuery('#golive-form .fib #fib_correct_bt').append('Wrong');
}
if( golive_fib_correct_bt == golive_fib_expected_bt){
jQuery('#golive-form .fib #fib_expected_bt').css({'background':'green','color':'#fff'});
jQuery('#golive-form .fib #fib_correct_bt').empty();
jQuery('#golive-form .fib #fib_correct_bt').append('Correct')
}
}
}

function getCSVData(){
 var csv_value=$('table').table2CSV({delivery:'value'});
 $("#csv_text").val();
}

function notification_nodejs_event(nid,status) {
  var count = parseInt(jQuery('.notify_num').text());
  count = count-1;
  jQuery('.notify_num').text(count);

 jQuery('#golive-acc-rej input').type = 'button';
  var input_val = '';
 if(status == 0) {
 input_val = 'Accept';
 }
 else {
   input_val = 'Reject';
 }

            var input_nid = nid;
             jQuery.ajax({
               url:Drupal.settings.basePath +"notification_save",
               data:{status:input_val,nid:input_nid}
            });

            jQuery('#edit-acc-re-fieldset'+nid).parent().hide();
            jQuery(this).parent().parent().append('<p class="txt_wrap" style="color: #FFFFFF;font-size: 20px;padding-top: 10px;text-align: center;">Status Update</p>');
  setTimeout("jQuery('p.txt_wrap').hide()", 2000);
}

// Go Live Multistep Form

function golive_multistep () {
//alert('test this');
jQuery('.golive_static h1').click ( function (){
jQuery(this).css({'background':'none','z-index':'0'});
jQuery(this).parent().css({'background':'none','z-index':'0','display':'none','opacity':'0'});
});
jQuery('#edit-field-go-live-subject').after().append('<div class="nxt one">Next</div>');
jQuery('#edit-field-user-status').after().append('<div class="prv one">Previous</div><div class="nxt two">Next</div>');
jQuery('#node_go_live_form_group_dnt').after().append('<div class="prv two">Previous</div>');
if(jQuery('#node_go_live_form_group_sub .form-type-textfield #edit-title').text() === ''){
jQuery('#node_go_live_form_group_fnds *').attr("disabled", "disabled");
jQuery('#node_go_live_form_group_dnt *').attr("disabled", "disabled");
jQuery('#node_go_live_form_group_fnds,#node_go_live_form_group_dnt').css({'background':'#87EEE8','opacity':'0.5'});

}
jQuery('.one.nxt').click(function () {
    jQuery('#node_go_live_form_group_fnds *').removeAttr('disabled');
    jQuery('#node_go_live_form_group_fnds').css({'background':'#E6C91E','opacity':'1'})
    jQuery('#edit-field-user-status-und-0-field-users-und-0-uid').focus();
});
jQuery('.two.nxt').click(function () {
    jQuery('#node_go_live_form_group_dnt *').removeAttr('disabled');
    jQuery('#node_go_live_form_group_dnt').css({'opacity':'1'})
    jQuery('#edit-field-time-und-0-value-datepicker-popup-0').focus();
    jQuery('#go-live-node-form #edit-submit').show();
});
jQuery('.one.prv').click(function () {
    jQuery('#node_go_live_form_group_dnt *').removeAttr('disabled');
    jQuery('#edit-title').focus();
});
jQuery('.two.prv').click(function () {
    jQuery('#edit-field-user-status-und-0-field-users-und-0-uid').focus();
});
}

function PrintDiv(er) {
  var divToPrint = document.getElementById(er);
  var popupWin = window.open('', '_blank', 'width=300,height=300');
  popupWin.document.open();
  popupWin.document.write('<html><body onload="window.print()">' + divToPrint.innerHTML + '</body></html>');
  popupWin.document.close();
}


//for the subscription form.
function subject_term_load(){
var l = window.location;
var base_url = l.protocol + "//" + l.host + "/" + l.pathname.split('/')[0];
jQuery('#edit-children').change( function () {
   var selected_tid = jQuery(this).val();
   window.location.href = base_url + 'subscription/form/' + selected_tid;
});
}

//for opening revision subject based on url
function subject_open_url(){
var l = window.location;
var base_url = l.pathname.split('/')[4];
jQuery('.subject').find("#" + base_url).css({'background':'#FDA22D','display':'block'});
}




function select_all_stat(obj1){ //all free selection
  var n = jQuery(obj1).val();
  var c = jQuery(".other-wrapper .form-type-checkbox").find('input[.form-checkbox][value=0]');
  if(n == '0'){
    jQuery(c).attr('checked', 'checked');
    jQuery(".form-type-checkbox").find('input[.form-checkbox][value=7]').attr('checked', false);
    //jQuery(".form-type-checkbox").find('input[.form-checkbox][value=7]').removeClass('radio-chk');
    //jQuery('.form-type-checkbox input').attr('checked',true);
  }
  else{
    // alert(n);
    jQuery(c).attr('checked', false);
    /*if(jQuery(obj1).hasClass('radio-chk')) {
      jQuery(obj1).removeClass('radio-chk');
      jQuery(obj1).attr('checked', false);
    }
    else {
      jQuery(obj1).addClass('radio-chk');
    }
    var gk_chk = jQuery(".radio-chk").not('#edit-duration-4-7').length;
    jQuery('.freespan').remove();
    if(gk_chk > 1) {
      jQuery('#edit-duration-4-7').attr('checked', 'checked');
      jQuery('#edit-duration-4-7').addClass('radio-chk');
      jQuery('#edit-duration-4-7').after('<span class="freespan" style= "padding-left:10px;">Complimentary</span>').show();
    }
    else {
      jQuery('#edit-duration-4-7').removeClass('radio-chk');
      jQuery('#edit-duration-4-7').attr('checked', false);
    }
    */
  }
}
// nit's code for subscription
function select_all(obj1){ //all free selection
  var n = jQuery(obj1).val();
  var c = jQuery(".other-wrapper").find('input[.form-checkbox][value=0]');
  // /alert(n);
  if(n == '0'){
    jQuery('#block-block-19').show();
    jQuery(c).attr('checked', 'checked');
    jQuery('.btn_subs_wrap #edit-addcart-submit').css('display','inline');
    jQuery('.btn_subs_wrap #edit-add-to-cart').css('display','none');

    jQuery(".form-type-checkbox").find('input[.form-checkbox][value=7]').attr('checked', false);
  }
  else{
    jQuery('#block-block-19').hide();
    jQuery('.btn_subs_wrap #edit-addcart-submit').css('display','none');
    jQuery('.btn_subs_wrap #edit-add-to-cart').css('display','inline');


    //checkbox id generate

    jQuery(c).attr('checked', false);
    /*
    if(jQuery(obj1).hasClass('radio-chk')) {
      jQuery(obj1).removeClass('radio-chk');
      jQuery(obj1).attr('checked', false);


    }
    else {
      jQuery(obj1).addClass('radio-chk');

    }

    var gk_chk = jQuery(".radio-chk").not('.gk-radio').length;
    jQuery('.freespan').remove();
    if(gk_chk > 1) {
      jQuery('.gk-radio').attr('checked', 'checked');
      jQuery('.gk-radio').addClass('radio-chk');
      jQuery('.gk-radio').after('<span class="freespan" style= "padding-left:10px;">Complimentary</span>').show();
    }
    else {
      jQuery('.gk-radio').removeClass('radio-chk');
      jQuery('.gk-radio').attr('checked', false);
    }
    //loop for checkbox check
    */
    jQuery(".form-type-checkbox").find('input[.form-checkbox][value=7]').each(function(){
      //console.log(jQuery(this).attr('id'));
      //console.log(jQuery(this).attr('checked'));
      $radio_id_arr = jQuery(this).attr('id').split("-");
      $chk_id = "#edit-subject-" + $radio_id_arr[2];
      if(jQuery(this).attr('checked') == 'checked') {
        jQuery($chk_id).attr('checked', "checked");
      }
      else  {
        jQuery($chk_id).attr('checked', false);
      }
    });
  }

}

function free_subscription (){

/*Free subscription*/
    jQuery('.page-subscription #messages .messages h2.element-invisible').remove();
    jQuery('.page-subscription #messages .messages').hide();
  a = jQuery('.page-subscription #messages .messages.status').last().text();
  //jQuery('.btn_subs_wrap').append('<div class="msg-st">'+a+'</div>');
  var b = a.indexOf("Thankyou for free Subscription");

  if(b == 0 && a != ''){
  var c = jQuery(".other-wrapper").find('input[.form-radio][value=0]');
  jQuery(c).prop("checked",true);
  jQuery('.msg-st').show();
  jQuery('.btn_subs_wrap #edit-addcart-submit').hide();
  jQuery('.btn_subs_wrap #edit-add-to-cart').hide();
  }
  else{
  var c = jQuery(".page-subscription .other-wrapper").find('input[.form-radio][value=0]');
  jQuery('.msg-st').hide();
  jQuery(c).prop("checked",false);
  jQuery('.btn_subs_wrap #edit-addcart-submit').css('display','none');
  jQuery('.btn_subs_wrap #edit-add-to-cart').css('display','inline');
  }


   if(Drupal.settings.subscription != undefined) {

    var free = Drupal.settings.subscription.free;

    var c = jQuery(".other-wrapper").find('input[.form-radio][value=0]');
    jQuery(c).prop("checked",true);
    jQuery('.msg-st').show();
    jQuery('.btn_subs_wrap #edit-addcart-submit').hide();
    jQuery('.btn_subs_wrap #edit-add-to-cart').hide();
  }



/*
  $(".page-subscription .form-type-checkbox input:not(:checked)").each (function () {
    var nid = $(this).val();
    var class_nm = ".form-item-duration-" + nid;

    var c = jQuery(".other-wrapper").find('input[.form-radio][value=0]');
    jQuery(class_nm +" input:radio").attr('disabled',true);

  });
*/

  var checked = $(".page-subscription .form-type-checkbox input:checked").length > 0;
    if(checked) {
      jQuery('#edit-add-to-cart').val('Update Cart');
    }
/*
  $(".page-subscription .form-type-checkbox input:checkbox").click( function(){
    var nid = $(this).val();
    var class_nm = ".form-item-duration-" + nid;

    if( $(this).is(':checked') ){
      jQuery(class_nm +" input:radio").attr('disabled',false);
    }
    else {
      var c = jQuery(".other-wrapper").find('input[.form-radio][value=0]');
      jQuery(c).attr('checked', false);

      jQuery(class_nm +" input:radio").prop('checked', false);
      jQuery(class_nm +" input:radio").attr('disabled',true);

    }
  });
*/
}


var active_link = jQuery( "#form-coupon-msg1" ).find( ".activate-coupon-code-link a" );
if(active_link){
//alert('hi');

}

jQuery( document ).ajaxComplete(function() {
if (jQuery("#generate-your-cart-status-block-form .activate-coupon-code-link" ).length > 0) {
   //$("#myid").length > 0 
console.log('aaaaaaa');
 jQuery('.activate-coupon-code-link a').parents('form#generate-your-cart-status-block-form').find('#edit-checkout-link').hide();
 jQuery('.activate-coupon-code-link').parents('form#generate-your-cart-status-block-form').find('#edit-checkout-link').hide();
}else if (jQuery("#generate-your-cart-status-block-form .activate-coupon-code-link a" ).length > 0) {
console.log('aAAAAA');
 jQuery('.activate-coupon-code-link a').parents('form#generate-your-cart-status-block-form').find('#edit-checkout-link').hide();
 jQuery('.activate-coupon-code-link').parents('form#generate-your-cart-status-block-form').find('#edit-checkout-link').hide();
}else{
  console.log('bbbbbbbbbbb');
  jQuery('form#generate-your-cart-status-block-form').not('activate-coupon-code-link').find('#edit-checkout-link').show();
 jQuery('form#generate-your-cart-status-block-form').not('activate-coupon-code-link a').find('#edit-checkout-link').show();
}
});
jQuery("document").ready(function() {
 jQuery('.activate-coupon-code-link a').parents('form#generate-your-cart-status-block-form').find('#edit-checkout-link').hide();
 jQuery('.activate-coupon-code-link').parents('form#generate-your-cart-status-block-form').find('#edit-checkout-link').hide();

});

jQuery("document").ready(function() {
jQuery('#generate-anonymous-your-cart-status-block-form').find('#edit-cart-details').parent().parent().show('');
jQuery('#generate-your-cart-status-block-form').find('#edit-cart-details').parent().parent().show('');
});

