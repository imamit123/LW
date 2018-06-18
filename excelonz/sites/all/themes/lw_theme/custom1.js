jQuery(document).ready(function(){
  jQuery('.page-dashboard-parent .highchart_area:odd, #block-lw-custom-user-detail #child_table:odd').addClass("odd");
  jQuery('.page-dashboard-parent  .highchart_area:even, #block-lw-custom-user-detail #child_table:even').addClass("even");

  jQuery('.pane-lw-report-parent-dashboard-chart .highcharts-container svg').children().attr('fill','Transparent');

  subscription_checkout ();
  uid_add_active();

  jQuery('#toboggan-login-link-container a').click(function (){
    jQuery(this).toggleClass('active_class');
  });

  accordian_script();

 /*JS for subscription*/
  jQuery('.other-wrapper .form-item.form-type-radios').eq(0).addClass('firstchild');

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
});**/

jQuery('#edit-profile-student-field-class-user-und-hierarchical-select-dropbox-add').val('Sure ?');


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
  jQuery('.line-item-summary-checkout a').bind('click', function(e){
    alert('To enable checkout, please click on T&C');
    e.preventDefault();
  });

  jQuery('.tc').click(function () {
    jQuery('.line-item-summary-checkout a').unbind('click');
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


