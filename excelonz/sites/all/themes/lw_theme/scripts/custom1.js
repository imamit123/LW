jQuery(document).ready(function(){
  jQuery('.page-dashboard-parent .highchart_area:odd, #block-lw-custom-user-detail #child_table:odd').addClass("odd");
  jQuery('.page-dashboard-parent  .highchart_area:even, #block-lw-custom-user-detail #child_table:even').addClass("even");

  if(jQuery('.addchilddetailsforsubscription #child_table .child-info').length == 1 ) {
    jQuery('.addchilddetailsforsubscription #main-content-header h1#page-title').text("Create Your Second Child's Account");
  }
  else if(jQuery('.addchilddetailsforsubscription #child_table .child-info').length == 2 ) {
      jQuery('.addchilddetailsforsubscription #main-content-header h1#page-title').text("Create Your Third Child's Account");
      jQuery('.addchilddetailsforsubscription #edit-submit--2').hide();
  }
  else {
     jQuery('.addchilddetailsforsubscription #main-content-header h1#page-title').text("Create Your Child's Account");
  }

  jQuery('.addchilddetailsforsubscription #user-register-form .form-item-pass-pass1 label').html("Select your Child's Password <span class='form-required' title='This field is required.'>*</span>");
  jQuery('.pane-lw-report-parent-dashboard-chart .highcharts-container svg').children().attr('fill','Transparent');
  jQuery('.page-user-edit.role-parent.child_edit #user-profile-form .form-type-password-confirm .form-item-pass-pass1 label').text("Select your Child's Password");
  jQuery('.class_div th').eq(0).show();
  jQuery('.class_div th').eq(1).show();
  subscription_checkout ();
  uid_add_active();
  add_active_child();
  previous_report_link();

  $(".tc input").attr('checked',false);
  jQuery('#toboggan-login-link-container a').click(function (){
    jQuery(this).toggleClass('active_class');
  });

  accordian_script();

  $('.chooseasubscriptionpackage #edit-add-to-cart').click(function(e){
    //e.preventDefault();  // stop the link from trying to navigate
    return validCommande();
  });
  jQuery('#subscription-form .form-radio').live('change',function() {
      jQuery('#edit-add-to-cart').unbind('click');
  });

 /*JS for subscription*/
  jQuery('.other-wrapper .form-item.form-type-checkboxes').eq(0).addClass('firstchild');
  jQuery('.other-wrapper .sub-checkbox').eq(0).addClass('firstchild');
  jQuery('.view-commerce-cart-block #views-form-commerce-cart-block-default .line-item-summary-checkout a').text('Continue to Next Step');

/*$('.edit.page-user #user-profile-form #edit-account .form-item-name #edit-name').attr('disabled','disabled');
$('.edit.page-user #edit-profile-student-field-class-user-und-hierarchical-select-selects-0').attr('disabled','disabled');
$('.edit.page-user #edit-profile-student-field-class-user-und-hierarchical-select-dropbox-add').attr('disabled','disabled');
$('.page-user-edit-student #edit-profile-student-field-class-user-und-hierarchical-select-dropbox-add').attr('disabled','disabled');*/
$('.pane-clone-of-golive-dashboard-upcoming .block-content').hide();
    $('.pane-clone-of-golive-dashboard-upcoming h2').click(function() {
      $(this).css('outline','none');
      if($(this).hasClass('active')) {
        $(this).next('.block-content').slideToggle('slow',function() {
        $(this).prev('h2').removeClass('active');
        $(this).parent().removeClass('parent');
      });
      }
      else {
        $('.pane-clone-of-golive-dashboard-upcoming .block-content').slideUp('slow',function() {
        $(this).prev('h2').removeClass('active');
        $(this).parent().removeClass('parent');
      });
      $(this).next('.block-content').slideToggle('slow',function() {
        $(this).prev('h2').toggleClass('active');
        $(this).parent().addClass('parent');
      });
      }
  });


/**
 $('.row-left').click(function(){
    $('.last-date, .close-click, .highcharts-chart').slideToggle('hide');
    if($(this).parent().hasClass('parent')){
      $( ".row-left" ).addClass( "newClass", 1000, callback );
      $(this).removeClass('row-left');
      return false;
    }
});




jQuery('#user-profile-form .add-to-dropbox').val('Sure ?');
jQuery('#user-profile-form .selects select').live('change',function()
    {
       jQuery('#user-profile-form .add-to-dropbox').val('Sure ?');
});

jQuery('#edit-profile-student-field-class-user-und-hierarchical-select-dropbox-add').val('Sure ?');
/*
  jQuery('#edit-profile-student-field-class-user-und-hierarchical-select-selects-0').live('change',function (){
  //jquery('#edit-profile-student-field-class-user-und-hierarchical-select-selects-1').
    jQuery("#edit-profile-student-field-class-user-und-hierarchical-select-selects-1 option:selected").remove();
    jQuery('#edit-profile-student-field-class-user-und-hierarchical-select-dropbox-add').val('ETST');
      console.log("test");
  });

  jQuery('#edit-profile-student-field-class-user-und-hierarchical-select-dropbox-add').live('click',function (){
    jQuery(this).val('Sure ?');
  });
*/



$(function() {
$( ".close-click" ).click(function(){
$('.last-date, .close-click, .highcharts-chart').slideToggle('hide');
$('.row-left').addClass('row-left1');
});

$( ".sp1" ).click(function(){
$('.last-date, .close-click, .highcharts-chart').slideToggle('show');
$('.row-left1').removeClass('row-left1');
});

});

$(".view-child-detail .views-field, .view-parent-profile-detail .views-field").each(function(i) {
    $(this).addClass("item" + (i+1));
        });

});



/* Checkout button will be disabled untill t&c will not be clicked*/
function subscription_checkout (){
  /*jQuery('.line-item-summary-checkout a').bind('click', function(e){
    alert('To enable Billing Summary, please click on T&C');
    e.preventDefault();
  });
*/
/*
  jQuery('#edit-addcart-submit').bind('click', function(e){
    alert('To enable Billing Summary, please click on T&C');
    e.preventDefault();
  });
*/

//revieworder checkout-buttons
  $('.revieworder .checkout-buttons div').prepend('<input class="jquery-cust-btn" type="submit" id="edit-back" name="op" value="Continue to next step">');
  $('.revieworder .checkout-processed').hide();


  jQuery('.jquery-cust-btn').click(function () {
    var isChecked = $('.tc input').attr('checked');
      if(isChecked != 'checked'){
        alert('To enable Billing Summary, please click on T&C');
        return false;
      }

  });

  jQuery('.tc input').click(function (){
      var isChecked = $('.tc input').attr('checked');
      if(isChecked == 'checked'){
        //jQuery('.line-item-summary-checkout a').unbind('click');
        jQuery('#edit-addcart-submit').unbind('click');
        //jQuery('.checkout-processed').unbind('click');
        jQuery('.revieworder .checkout-processed').show();
        jQuery('.revieworder .jquery-cust-btn').hide();
      }
      else {
        jQuery('.revieworder .checkout-processed').hide();
        jQuery('.revieworder .jquery-cust-btn').show();
      }
   });


}

/* Add Active class based on url on children name*/
function uid_add_active(){
  var l = window.location;
  var uid = l.pathname.split('/')[3];
  jQuery('.subs_child_classa li').each(function () {
      a = jQuery(this).attr('id');
      if( uid  == a){
        jQuery(this).addClass('active');
      }
  });
}

/* JS for accordian */

function accordian_script(){

  $('.subject_report .row,.subject-start .test .sub_main,.subject-start .test .subject-topic').hide();
  $('.subject-start .test .sub_main,.subject-start .test .subject-topic,.subject-start .row').show();
  $('.subject .subject-main,.subject-start #main_class').addClass('active');
  $('.page-topic-progress-report .subject_report .row').eq(0).show();
  $('.page-topic-progress-report .subject_report .row').eq(1).show();
  $('.page-teacher-topic-progress .subject_report .row').eq(3).show();
  $('.page-assessment .subject_report .row').eq(1).show();
  $('.page-assessment .subject_report .row').eq(3 ).show();
  $('.page-report-performance .subject_report .row').eq(2).show();
  $('.page-assessment .subject_report .lft').eq(1).addClass('active');
  $('.page-assessment .subject_report .lft').eq(3).addClass('active');
  $('.page-topic-progress-report .subject_report .lft').eq(0).addClass('active');
  $('.page-topic-progress-report .subject_report .lft').eq(1).addClass('active');
  $('.page-report-performance .subject_report .lft').eq(2).addClass('active');
  $('.page-teacher-topic-progress .subject_report .lft').eq(3).addClass('active');
  $('.page-topic-progress-report .subject_report .lft').eq(2).addClass('active');
  $('.page-topic-progress-report .subject_report .row').eq(2 ).show();
  $('.page-teacher-topic-progress .subject_report .sp1 a.active').parent().parent().parent().show();
  $('.page-teacher-topic-progress .subject_report .sp1 a.active').parent().parent().parent().prev().addClass('active');
  /* Expand all tabs*/
  $('#expand').click(function (){
    $(this).hide();
    $('#collapse').show();
     $('.view-id-experiments .views-table').addClass('active');
    $('.subject_report .lft,.subject .subject-main,.subject-start #main_class,.view-id-experiments .views-table caption').addClass('active');
    $('.subject_report .row,.subject  .subject-topic,.subject-start .row,.view-id-experiments .views-table tbody').show();
  });

  /* Collased All tabs*/
  $('#collapse').click(function (){
    $(this).hide();
    $('#expand').show();
    $('.subject_report .lft,.subject .subject-main,.subject-start #main_class,.view-id-experiments .views-table caption').removeClass('active');
    $('.view-id-experiments .views-table').removeClass('active');
    $('.subject_report .row,.subject  .subject-topic,.subject-start .row,.view-id-experiments .views-table tbody').hide();
  });

  $('.subject_report .lft,.subject .subject-main,.subject-start .test #main_class').each(function(){
    var $content = $(this).next();
    $(this).click(function(e){
      e.preventDefault();
      $(this).toggleClass('active');
      $content.not(':animated').slideToggle();
    });
  });

  /*
experiments accordian js
 */
$(".view-id-experiments .views-table tbody").hide();
$(".view-id-experiments .views-table caption").each(function(){
    var $content = $(this).next();
    $(this).click(function(e){
      e.preventDefault();
      $(this).toggleClass('active');
      $(this).parent().toggleClass('active');
      $content.not(':animated').slideToggle();
    });
});

/* Expand Play Off Tabs*/
  $('#collapse_link').hide();
  $('#expand_link').click(function (){
    $(this).hide();
    $('#collapse_link').show();
    $('.pane-clone-of-golive-dashboard-upcoming .block-inner').addClass('parent');
    $('.pane-clone-of-golive-dashboard-upcoming .block-title').addClass('active');
    $('.pane-clone-of-golive-dashboard-upcoming .block-content').show();
  });

  /* Collased All tabs*/
  $('#collapse_link').click(function (){
    $(this).hide();
    $('#expand_link').show();
    $('.pane-clone-of-golive-dashboard-upcoming .block-inner').removeClass('parent');
    $('.pane-clone-of-golive-dashboard-upcoming .block-title').removeClass('active');
    $('.pane-clone-of-golive-dashboard-upcoming .block-content').hide();
  });

/*
$('.subject_report .row').hide();
$('.subject_report:last .row').show();
$('.subject_report:nth-child(3n) .row').show();
$(".page-report-performance-parent .subject_report, .page-assessment-home-student .subject_report").click(function(){
jQuery(this).prevAll(".subject_report").find(".row").slideUp();
    jQuery(this).nextAll(".subject_report").find(".row").slideUp();
});
  jQuery('div.subject_report span').click(function() {
    jQuery(this).toggleClass('actives');
    jQuery(this).next('div.row').slideToggle('slow')
    .siblings('div.row:visible').slideUp('slow');

  });

  jQuery('.experiment-expand').click(function () {
    jQuery('.view-experiments .views-table tbody').css('display','table-row-group');
  });
  jQuery('.view-experiments .views-table').click(function () {
    jQuery('.view-experiments .views-table').removeClass('active');
    jQuery(this).addClass('active');
  });
  jQuery('.topic_tittle .exp').click(function () {
    jQuery('.subject_report .lft').addClass('active');
    jQuery('.subject_report .row').show();
  });
  jQuery('.subject_report span.lft').click(function () {
    jQuery('.subject_report span.lft').removeClass('active');
    jQuery(this).addClass('active');
  });
*/

}

/* Add active class based on clicked child */

function add_active_child(){
  var l = window.location;
  var a = l.pathname.split('/')[3];
  jQuery('.subs_child_classa li').each(function (){
    b = jQuery(this).attr('id');
    if( a == b){
      jQuery(this).addClass('active');
      jQuery(this).removeClass('non-active');
    }
    else{
      jQuery(this).addClass('non-active');
      jQuery(this).removeClass('active');
    }
  });
}

/* Back to Previous report */

function previous_report_link(){
  $('.teach_link .one.back').click(function(){
      parent.history.back();
      return false;
  });
}

function validCommande(events) {
    var paiement = $("#subscription-form  #edit-subject .form-checkbox:checked").val();
    var duration = $("#subscription-form  #edit-subject .form-checkbox:checked").val();
    var a = $("#subscription-form .form-radio:checked").val();
    var b = $("#subscription-form .form-checkbox:checked").val();
     if (!$("#subscription-form .form-checkbox:checked").val() && !$("#subscription-form .form-radio:checked").val() ) {
      alert('please choose subject and duration');
      //events.preventDefault();
      return false;
    }
    else{

      jQuery('#edit-add-to-cart').unbind('click');
      return true;
    }
}

