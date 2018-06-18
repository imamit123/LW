
jQuery(document).ready(function(){

datainput1 = parseInt(Drupal.settings.revision_time.duration);

if(datainput1 == 600) {
//  jQuery('.rev_markup p').text("Revise all you want!");
  return;
}

var count = datainput1 * 60;
  var sec = 0;
  var min = 0;
    var timer = $.timer(
      function() {
        count--;
        if(count === 0) {

          var l = window.location;
          var base_url = l.protocol + "//" + l.host + "/" + l.pathname.split('/')[0];

          var url_red = base_url + "revision-report";
          window.location.href = url_red;

        }
//        alert(count);
        cur_time = count;
        min = count / 60;
        //min = ("0" + min).slice(-2);
        if(count < 60 )
          {min = 00;}
        sec = Math.round(count % 60);
        sec = ("0" + sec).slice(-2);
        $('.revisiontime').html(Math.floor(min) + ':'  + sec);
      },
      1000,
      true
    );

});


