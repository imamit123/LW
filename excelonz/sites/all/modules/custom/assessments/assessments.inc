<?php
/**
 * @file
 *
 */

/**
 *  Function to generate the form.
 *  This function will call for the first time when assessment is started.
 *  Steps
 *    - Generate random question Id.
 *    - Generate form structure.
 */
function assessments_form($form, &$form_state) {

  $curr_time = 0;
  if (array_key_exists('start_time', $_SESSION)) {
    $curr_time = time() - $_SESSION['start_time'];
  }

  drupal_add_js(array(
    'timer_settings' => array(
      'curr_time' => $curr_time ,
    ),
  ),
  'setting');

  //drupal_add_js('http://code.jquery.com/jquery-1.4.4.min.js'); // prateek
  //drupal_add_js('http://code.jquery.com/jquery-1.7.2.min.js'); // prateek
  //drupal_add_js('http://code.jquery.com/ui/1.8.21/jquery-ui.min.js'); // prateek
  //@todo : move js to the type where it is required.
  drupal_add_js( drupal_get_path('module', 'assessments') . '/assessments.js');
  drupal_add_js( drupal_get_path('module', 'assessments') . '/timer.js');
  drupal_add_css( drupal_get_path('module', 'assessments') . '/assessments.css');
  //drupal_add_js( drupal_get_path('module', 'assessments') . '/jquery.ui.touch-punch.min.js');// prateek


  //Check for form submit and redirect user.
  if (array_key_exists('values', $form_state)) {

    if ($_POST['opt'] == "Correct") {
      $_SESSION['correct_ans']++;
      $_SESSION['level_correct_ans']++;
      $_SESSION['level_wrong_ans'] = 0;
      $_SESSION['user_orig_exc']++;
      $_SESSION['user_session_exc']++;
    }
    elseif ($_POST['opt'] == "Wrong") {
      $_SESSION['wrong_ans']++;
      $_SESSION['level_wrong_ans']--;
      if ($_SESSION['level_wrong_ans'] == 0 && $_SESSION['user_current_level'] != 1) {
       // downgrade_lod();
      }
      else {
        $_SESSION['level_up'] = 'not_started';
      }
    }
    $_SESSION['timer_value'] = $_POST['timer_value'];

    drupal_goto('assessments-report');
  }
  else {
    //for refresh scenario
    if($_SESSION['topic_tid'] != $_GET['tid']) {
      unset($_SESSION['report_id']);
      $_SESSION['correct_ans'] = 0;
      $_SESSION['wrong_ans'] = 0;
    }
  }

  //@todo : remove below unset variable.
  //unset($_SESSION['qid']);
  if (array_key_exists('qid', $_SESSION)) {
    $qid = $_SESSION['qid'];
    //$qid=220;
  }
  else {
    $qid = assessment_random_question();
    $_SESSION['qid'] = $qid;
    //$qid=220;
  }
  if($_SESSION['free_sub'] && $_SESSION['user_current_level'] > 1) {
      $form1 = get_free_subscription_form();


    assessment_report_unset();
    return $form1;
  }
  $form = assessment_generate_form($qid);


  global $base_url;
  $node = node_load($qid);
  //echo "<pre>";print_r($node);die();
  $n_type = $node->type;
  $form['timer_value'] = array(
    '#type' => 'textfield',
    '#title' => t('timer_value'),
    '#size' => 10,
    '#maxlength' => 128,
  );
  $form['timer'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="timer"><span class="startstoptime">0:00</span><p>mins spent</p></div>',
    '#weight' => -102,
  );
  $form['sure'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="btn-wrap '.$n_type.'"><div class="btn-wrap-inner"><p class="sure">Are You Sure ?</p>',
  );
  $form['sub'] = array(
    '#type' => 'markup',
    '#markup' => '<button id="submit-button" type="button">Yes</button>',
  );
  $form['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<button id="reset" type="button">No</button></div></div>',
  );
  $form['action']['next'] = array(
    '#prefix' => '<div class="'.$n_type.'">',
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'assessment_next',
      'wrapper' => array('option-list'),
      'name' => 'next',
    ),
    '#value' => t('Next'),
    '#suffix' => '<script>remove_div();</script></div>',
    //'#weight' =>  100,
  );
  $form['finish'] = array(
    '#type' => 'button',
    '#value' => 'Finish',
    // '#weight' => -109,
  );


   $topic = taxonomy_term_load($_SESSION['topic_tid']);
   $parents = taxonomy_term_load($_SESSION['subject_tid']);
  //echo '<pre>';print_r($node);die();
  $topic_name = $topic->name;
  $subject_name = $parents->name;
  $form['head'] = array(
    '#type' => 'markup',
    '#markup' => '<div class= "assessment-header-top"><h3 class= "assessment-header">'.$subject_name." : ".$topic_name.'</h3></div><div class="assessment_wrap">',
    '#weight' => -109,
  );

  return $form;
}


/**
 * This function will call when next button will be clicked.
 */
function assessment_next($form, $form_state) {
$_SESSION['timer_value'] = $form_state['values']['timer_value'];
  $nid = $_SESSION['qid'];
  //It will fetch ans from hidden textbox.
  if ($_POST['opt'] == "Correct") {
    $_SESSION['correct_ans']++;
    $_SESSION['level_correct_ans']++;
    //$_SESSION['level_wrong_ans'] = 0;
    update_lod_down_session();
    $_SESSION['user_orig_exc']++;
    $_SESSION['user_session_exc']++;

    skillmap_record($nid, TRUE, $_SESSION['subject_tid']);
   if (strpos($_SESSION['level_up'],'OOPS you are back to') !== false) {
         $_SESSION['level_up'] = 'not_started';
    }



  }
  else {
    skillmap_record($nid, FALSE, $_SESSION['subject_tid']);

    $_SESSION['wrong_ans']++;
    $_SESSION['level_wrong_ans']--;
    if ($_SESSION['level_wrong_ans'] == 0 && $_SESSION['user_current_level'] != 1) {
      //downgrade_lod();
    }
    else {
      $_SESSION['level_up'] = 'not_started';
    }
  }

  $qid = assessment_random_question();
  $_SESSION['qid'] = $qid;
  if ($qid == '')  {
    $form1['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="option-list">',
      '#markup' => '<div class="no_more_ques"><img src="/sites/default/files/field/image/no_more_ques_0.jpg"/></div>',
      '#suffix' => '</div>',
    );
  }
  elseif($_SESSION['free_sub'] && $_SESSION['user_current_level'] > 1) {
    $form1 = get_free_subscription_form("second");
    //assessment_report_unset();
    return $form1;
  }
  else {
    $form1 = assessment_generate_form($qid);
  }


  return $form1;
}


/**
 * function to select random question
 */
function assessment_random_question() {
  global $user;
  $uid = $user->uid;



  //call this function for the fist time only.
  if (!array_key_exists('user_class_value', $_SESSION)) {
  //if (TRUE) {
    $_SESSION['start_time'] = time();
    $_SESSION['level_wrong_ans'] = 0;

    //fetch users profile ID.
    $pid_query =   //fetch users profile ID.
    $pid_query = db_select('profile', 'p')
    ->fields('p',array('pid'))
    ->condition('uid',$uid)
    ->condition('type','student')
    ->range(0, 1)
    ->execute()
    ->fetchAll();
    $pid = $pid_query[0]->pid;

    //fetch user class name.
    $query = db_select('field_data_field_class_user', 'c');
    $query->join("taxonomy_term_data", "uc", "c.field_class_user_tid=uc.tid");
    $query->fields('uc')
      ->condition('c.entity_id', $pid)
      ->condition('c.delta', 0);
    $result = $query->execute()
      ->fetchAssoc();

    $topic_tid = $_GET['tid'];
    $subject_tid = $_GET['ptid'];

     $info_subject = taxonomy_term_load($_GET['ptid']);
     $info_topic = taxonomy_term_load($_GET['tid']);

     //fetch user level in current topic
     $query1 = new EntityFieldQuery();
     $query1->entityCondition('entity_type', 'user_info')
      ->propertyCondition('uid', $uid)
      ->propertyCondition('subject_tid', $subject_tid)
      ->propertyCondition('topic_id', $topic_tid)
      ->range(0, 1);
    $result1 = $query1->execute();

    if (isset($result1['user_info'])) {
      $ui_ids = array_keys($result1['user_info']);
      $ui_id = $ui_ids[0];
      $ui_info = entity_load_single("user_info", $ui_id);
      $level = $ui_info->level;

    }
    else {

      $entity = entity_create("user_info",
      array('subject' => $info_subject->name,
        'uid' => $user->uid,
        'type' => 'user',
        'level' => 1,
        'topic' => $info_topic->name,
        'topic_id' => $topic_tid,
        'subject_tid' => $subject_tid,
        'total' => 1
        ));
      $en = entity_save('user_info', $entity);
      $level = 1;


    }

    $class = $result['name'];

    $_SESSION['class'] = $result['tid'];
    $_SESSION['user_class_value'] = $class;
    $_SESSION['user_current_level'] = $level;
    $_SESSION['level_correct_ans'] = 0;

    $exc_query = db_select('field_data_field_excellone', 'e')
        ->fields('e')
        ->condition('entity_id', $user->uid)
        ->range(0, 1)
        ->execute()
        ->fetchAll();
    $_SESSION['user_orig_exc'] = $exc_query[0]->field_excellone_value;

    $_SESSION['user_session_exc'] = 0;


      /* freelevel1restrict */
        $_SESSION['free_sub'] = is_free_subscription();
      /* freelevel1restrict */
  }

  $question_level_id = get_current_question_level($_SESSION['user_current_level']);

  //@todo : filter queries on question subject filter. Need to set subject in workflow.
  //@todo : remove level of difficulty from user field and need to store it with relation to subject.

  // if session key exist then fetch all the info from there and display the random question
  if (array_key_exists('question_asked', $_SESSION) && array_key_exists("question_level", $_SESSION)) {


    $class_term_id = $_SESSION['class'];
    $topic_tid = $_SESSION['topic_tid'];
    //Query to fetch random question according to class and level.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1)
      ->propertyCondition('nid', $_SESSION['question_asked'], 'NOT IN')
      ->fieldCondition('field_class', 'tid', $class_term_id, '=')
      ->fieldCondition('field_question_level', 'tid', $question_level_id, '=')
      ->fieldCondition('field_subjects', 'tid', $topic_tid, '=')
      ->addTag('random')
      ->range(0, 1);

    $result = $query->execute();
    if (isset($result['node'])) {
      $news_items_nids = array_keys($result['node']);
      $nid = $news_items_nids[0];
    }

    $_SESSION['question_asked'][] = $nid;
    return $nid;
  }
  else {
  /**
    * user will come here when first question of assessment arrive
    *  - fetch tid for class and level
    *  - exicute query for fetching the question
    */

    //$class_id = taxonomy_get_term_by_name($class);
    //@todo : use array_keys instead of foreach
    //foreach ($class_id as $cid) {
    //  $class_term_id = $cid->tid;
    //}

    $topic_tid = $_GET['tid'];


    $_SESSION['question_level'] = $question_level_id;
    // $_SESSION['class'] = $class_term_id;
    $_SESSION['topic_tid'] = $topic_tid;
    $_SESSION['subject_tid'] = $_GET['ptid'];


    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_class', 'tid', $_SESSION['class'], '=')
      ->fieldCondition('field_question_level', 'tid', $question_level_id, '=')
      ->fieldCondition('field_subjects', 'tid', $topic_tid, '=')
      ->addTag('random')
      ->range(0, 1);

    $result = $query->execute();
    if (isset($result['node'])) {
      $news_items_nids = array_keys($result['node']);
      $nid = $news_items_nids[0];
    }
    $_SESSION['question_asked'] = array();
    $_SESSION['question_asked'][] = $nid;

    return $nid;
  }
}


/**
 * This function will generate form and return it.
 */
function assessment_generate_form($qid) {
  // $qid = 160252;

  //$qid = 165868;
  global $base_url;
  global $user;
  $node = node_load($qid);
  $n_type = $node->type;

  $name = '';
  if(array_key_exists('name', $_SESSION)) {
    $name = $_SESSION['name'];
  }
  else {
    $name = user_load($user->uid);
    $name = $name->field_first_name['und'][0]['value'];
    $_SESSION['name'] = $name;
  }
  //echo '<pre>';print_r($node);die();
  //@todo : put it in proper content type - nitish.
  if (array_key_exists('und', $node->field_question_image)) {
    $quest = '';
    $img_path = '';
    $size = '';
    $img_width = '';
    $img_with_txt = '';
    $img = $node->field_question_image['und'][0]['uri'];
    $style = 'question_large_688_image';
    $img_path = image_style_url($style, $img);
    $size = getimagesize($img_path);
    $img_width =  $size[0];
    //echo '<pre>';print_r($size);die();
    //$quest =  "<img src='" . $base_url . "/sites/default/files/" . $img . "' />";
    $quest =  "<img src='".$img_path."' />";
    if ($img_width < 450){
      $img_with_txt = '<div class="queston_img" style="float:left;width:'.$img_width.'">'.$quest.'</div>';
    }
    else {
      $img_with_txt = '<div class="queston_img" style="float:left;width:100%">'.$quest.'</div>';
    }

  }
  // for displaying answer description
  $ans_desc_link = '';
  if (array_key_exists('und', $node->field_question_description)) {
    $ans_desc = $node->field_question_description['und'][0]['value'];
      if ($ans_desc) {
    //$ans_expl_img = $img = $node->field_question_image['und'][0]['uri'];
    $style = 'question_large_688_image';
    $ans_desc_link = "<div class='descs'>
                        <p class='shwtxt'>More About This</p>
                        <div class='ans_desc'>
                          <span class='cl'>X</span>
                          <div class='ans_shw' style='min-height:200px;'>" . $ans_desc . "</div>
                        </div>
                      </div>";
     }
  }
  if (array_key_exists('und', $node->field_answer_explanation_img)) {
    $ans_exp_uri = $node->field_answer_explanation_img['und'][0]['uri'];
    if($ans_exp_uri != '') {

        $style = 'ans_exp_img';
        $img_path = image_style_url($style, $ans_exp_uri);
        $quest =  "<img src='".$img_path."' />";
        $ans_desc_link = "<div class='descs'>
                        <p class='shwtxt'>More About This</p>
                        <div class='ans_desc'>
                          <span class='cl'>X</span>
                          <div class='ans_shw'>" . $ans_desc . "</div>
                          <div class='ans_shw_img'>" . $quest . "</div>
                        </div>
                      </div>";
    }
  }

  $level_msg = $_SESSION['level_up'];


  $opt1 = '<div class="answer-option opt">';//prateek added 'answer-option' class in opt div also added <ul> just after opt div
  $opt = '';
  if ($n_type == 'mcq') {
    foreach ($node->field_question_options['und'] as $option) {
      //@todo : use entity_load_single then will change $option[value] after 4 line.
      $options = entity_load("field_collection_item", array($option['value'], ));
      //echo '<pre>';print_r($options);die();
      $val = $options[$option['value']]->field_correct_answer['und'][0]['value'];
      $ans_img = $options[$option['value']]->field_image_option['und'][0]['filename'];
      //check if user class is less then 3 then add code for drag and drop.
      //print $options[$option['value']]->field_option_1['und'][0]['value']; die();
      /*if (array_key_exists('und', $options[$option['value']]->field_option_1)) {
        if ($_SESSION['user_class_value'] > 3) {
          $opt .= "<div class='button-option ".$n_type."'><button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>" . $options[$option['value']]->field_option_1['und'][0]['value'] . "</button></div>";
        }
        else {
          $opt .= "<div class='button-option ".$n_type."'><button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>" . $options[$option['value']]->field_option_1['und'][0]['value'] . "</button></div>";
        }
      }*/
      if (array_key_exists('und', $options[$option['value']]->field_image_option)) {
         $img_path_mcq = '';
         $img_mcq = '';
         $img_path_mcq = '';
         $opt_img = '';
         $img_txt_label = '';
         $img_mcq = $options[$option['value']]->field_image_option['und'][0]['uri'];

         $style_mcq = 'answer_img_mcq';
         if($options[$option['value']]->field_option_1['und'][0]['value']){
          $img_txt_label = '<div class=ans-bt-img>'.$options[$option['value']]->field_option_1['und'][0]['value'] .'</div>';
         }


         $img_path_mcq = image_style_url($style_mcq, $img_mcq);
        if ($_SESSION['user_class_value'] > 3) {
          $opt .= "
          <div class='button-option withimg ".$n_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <img src='".$img_path_mcq."' />
              ".$img_txt_label."
            </button>
          </div>";
        }
        else {
          $opt .= "
          <div class='button-option withimg ".$n_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <img src='".$img_path_mcq."' />
              ".$img_txt_label."
            </button>
          </div>";
        }
      }
      else {
         if ($_SESSION['user_class_value'] > 3) {
          $opt .= "
          <div class='button-option noimg ".$n_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <div class='ans-bt'>" .$options[$option['value']]->field_option_1['und'][0]['value'] . "</div>
            </button>
          </div>";
        }
        else {
          $opt .= "
          <div class='button-option noimg ".$n_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <div class='ans-bt'>" . $options[$option['value']]->field_option_1['und'][0]['value'] . "</div>
            </button>
          </div>";
        }
      }
    }
  $opt .= "<div class='clicker ".$n_type." '><textarea name= 'opt' class='give_val' style='display:none' ></textarea></div>";
  }

  //start of true and false
  if ($n_type == 'true_and_false') { // moved the true and false out of MCQ
    foreach ($node->field_answer_choices['und'] as $option) { // change in the field collection name
      $options = entity_load("field_collection_item", array($option['value'], ));

    //echo "<pre>";print_r($options);die();
    $val1 = $options[$option['value']]->field_option_1['und'][0]['value'];
    if($val1 == "") {
      $img_tf = $options[$option['value']]->field_image_option['und'][0]['uri'];
     // echo $img_tf;
      $img_tf_path = image_style_url("truandfalse", $img_tf);
        $val1 =  "<img src='".$img_tf_path."' />";
    }
    //echo $val1;die();


      $val = $options[$option['value']]->field_correct_answer['und'][0]['value'];
      $opt .= "<div class='button-option ".$n_type."'><button id=" . $val . " class='input_class " . $val . "' type='button' name=" . $val . "><div class='ans-bt'>" . $val1 ."</div></button></div>";
    }
    $opt = $opt1 . $opt . "</div><div class='clicker ".$n_type." '>
      <textarea name= 'opt' class='give_val' style='display:none' ></textarea></div>";
  }

  // Fill in the blank question type
  if ($n_type == 'fib') {
    $ans_desc = '';
    $question_title = '';
    $pos = '';
    $strlength = '';
    $strlength1 = '';
    $strlength2 = '';
    $strlength3 = '';
    $chars = '';
    $ch1 = '';
    $ch2 = '';
    $ch3 = '';
    //echo '<pre>';print_r($node);die();
    // Code for fetch word starting with special character from question text.
    $question_title = $node->field_question_text['und'][0]['value'];
    //print $question_title;die();
    $pattern = '#@([^~]+)@#'; // If '~' character found in fib question then fib will not work
    preg_match($pattern, $question_title, $matches);
    //echo '<pre>';print_r($matches);die();
    $chars = preg_split('/ /', $matches[1], -1, PREG_SPLIT_OFFSET_CAPTURE);
    $ch1 = $chars[0][0];
    $ch2 = $chars[1][0];
    $ch3 = $chars[2][0];
    $strlength = array();
    $j = 0;
    $blank_str2 = '<span class="fib_area">';
    $blank_input2 = '';
    foreach ($chars as $key => $value) {
      $blank_str2 .= "<span class='fib_word'>";
      for($i = 0 ; $i < strlen($value[0]) ; $i ++) {
        $blank_str2 .= '_ ';
        $blank_input2 .= '<input class="userenter one in-'.$i.'" type="text" maxlength="1" autofocus="autofocus" />';
      }
      $blank_str2 .= "</span>";
      $blank_input2 .= "&nbsp;&nbsp;&nbsp;&nbsp;";
    }
    $blank_str2 .= "</span>";
/*
    for($i = 0 ; $i < $strlength1 ; $i ++)
    {
      $blank_str .= '_ ';
      $blank_input .= '<input class="userenter one" type="text" maxlength="1" autofocus="autofocus" />';
    }
    for($i = 0 ; $i < $strlength2 ; $i ++)
    {
      $blank_str1 .= '_ ';
      $blank_input1 .= '<input class="userenter two" type="text" maxlength="1" autofocus="autofocus" />';
    }
    for($i = 0 ; $i < $strlength3 ; $i ++)
    {
      $blank_str2 .= '_ ';
      $blank_input2 .= '<input class="userenter three" type="text" maxlength="1" autofocus="autofocus" />';
    }
    */

    //$blank_input2 = $blank_input.'<br />'.$blank_input1.'<br />'.$blank_input2;
    //$blank_str2 = '<span class="fib_area">'.$blank_str.'&nbsp;&nbsp;'.$blank_str1 .'&nbsp;&nbsp;'.$blank_str2.'</span>';

    //Code for remove word starting with special character from question text and insert blank spaces
    $question_title_val =  preg_replace("#@([^~]+)@#",$blank_str2, $question_title);
    $opt = '<div class="keyarea"><div id="fib_expected">'.$blank_input2.'<p class="mergeval"></p><div class="clrtxt">Clear Text</div></div><textarea id="fib_correct"  style="display:none;" >' . $matches[1] . '</textarea><textarea id="fib" name= "opt" class="give_val" style="display:none;" ></textarea></div>';
  }

  // For Jumbled/Unjumbled question type
  if ($n_type == 'jumble') {
    $jumble_wrap = '';
    $jumb_def_ques = '';
    $val_jumb = '';
    $random1 = array();
    $j = 0;
    foreach ($node->field_correct_word['und'] as $option) {
      if(strlen($option['value']) > 1) {
        $val_jumb .= $option['value'] . ' ';
      }
      else {
        $val_jumb .= $option['value'];
      }
      $random1[] = $option['value'];

      $default_text = $val_jumb ;
    }

    shuffle($random1);
   //echo '<pre>';print_r($random1);die();
    foreach ($random1 as $options) {
      $val .= '<li class="ui-draggable j_word"><div class="extra"><span> '.$random1[$j].' </span></div></li>';
      $jumble_wrap = '<div class="answer-option"><ul>'.$val.'</ul></div>';
      $j++;
   }
  }

  // For Match the following content type
  if ($n_type == 'match_the_following') {
    $match_question = '';
    $match_question_wrap = '';
    $match_ans_wrap = '';
    $correct_match = '';
    $img1 = '';
    $img2 = '';
    $img3 = '';
    $img_path_m1 = '';
    $img_path_m2 = '';
    $img_path_m3 = '';
    $img_name = '';
    $random = array();
    foreach ($node->field_correct_match_word['und'] as $option) {
      $random[] = $option['value'];
    }

    shuffle($random);
    $i = 0;
    foreach ($node->field_correct_match_word['und'] as $option) {
      $options = entity_load("field_collection_item", array($option['value'], ));
      $options1 = entity_load("field_collection_item", array($random[$i], ));
      $img_match = $options[$option['value']]->field_image_option['und'][0]['uri'];
      $img_match_correct = $options[$option['value']]->field_correct_image['und'][0]['uri'];
      $img_match_random = $options1[$random[$i]]->field_correct_image['und'][0]['uri'];
      $style_match = 'match_120x112';
      $img_path_m1 = image_style_url($style_match, $img_match);
      $img_path_m2 = image_style_url($style_match, $img_match_correct);
      $img_path_m3 = image_style_url($style_match, $img_match_random);
      if ($img_match) {
        $img1 = '<img src="'.$img_path_m1.'" />';
      }
      if ($img_match_correct) {
        $img2 = '<img src="'.$img_path_m2.'" />';
      }
      if ($img_match_random) {
        $img3 = '<img src="'.$img_path_m3.'" />';
      }
      if($options1[$random[$i]]->field_correct_image['und'][0]['filename']){
        $img_name = $options1[$random[$i]]->field_correct_image['und'][0]['filename'];
      }
      if($options[$option['value']]->field_correct_image['und'][0]['filename']){
        $img_name2 = $options[$option['value']]->field_correct_image['und'][0]['filename'];
      }
      $match_question_wrap .= '
      <ul><li>
        <div class="col1">
          <div class="col1-box">
              '.$img1 .$options[$option['value']]->field_given_word['und'][0]['value'].'
              <div class="col1-arrow"></div>
          </div>
        </div>
        <div class="drag-area col2">
          <ol class="box-area placeholder"></ol>
          <p class="correct_match">
            '.$img2 .$options[$option['value']]->field_correct_match['und'][0]['value'].'
          </p>
        </div>
      </li></ul>';
      $val .= '
      <div class="match_drag_box">
        <ul>
          <li class="ui-draggable match">
            '.$img3.'<b style ="display:none">'
            . $img_name.'</b>'.
            $options1[$random[$i]]->field_correct_match['und'][0]['value'].'
          </li>
        </ul>
      </div>';
      $correct_match .= '
        <ul>
          <li>'.
            $img_name2.$options[$option['value']]->field_correct_match['und'][0]['value'].'
          </li>
        </ul>';
      if ($img_match) {
        $match_question_wrap = '<div class="img-match">'.$match_question_wrap.'</div>';
      }
      $match_ans_wrap = '<div class="answer-option">'. $val.'</div>';
      if ($img_match_correct) {
        $match_ans_wrap = '<div class="answer-option img_match_correct">'. $val.'</div>';
      }
      $i++;
    //  echo "--" . $option['value'];
    }
    //die();
    //print ($match_ans_wrap);die();
    drupal_add_js( drupal_get_path('module', 'assessments') . '/assessments.js');
  }
  $question_lod_print = "Question lod " . $_SESSION['question_lod'] . '<br/>';
  //$question_level_print = 'Question Level = ' . $_SESSION['level_name'] . "<br/>";

  //adding radio button to markup as it will be replaced by div for 1-3
  //and ajax is not fetching radion button in ajax callback
  //print ($_SESSION['correct_ans']);die();
    $level_markup = '<div class="label-bg"><ul class="label">' ;
    for ($i = 1 ; $i<6 ; $i++) {
      if($i <= $_SESSION['user_current_level']) {
        $class_text = 'label-over-'.$i;
      }
      else {
        $class_text = 'label-'.$i;
      }
      $level_markup .=  '<li class="'.$class_text.'"><span>'.$i.'</span></li>';
    }
    $level_markup .= "</ul>";
    $level_markup .= '<div class="label-text">levels';
    $level_markup .= "</div></div>";

    if($_SESSION['revision']['time'] == "unlimited") {
      $revision_markup = '<div class="rev_markup"><p>Revise all you want!</p></div>';
    }
    else {
      $revision_markup = '<div class="rev_markup"><p>Timed Test</p></div>';
    }
  $form['option'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="option-list">',
    '#markup' =>  //$question_level_print .


    '<div class="right_exl_block mcqndtf '.$arg_value.'"><div class="session_ex2"><h2>'.$name.'<span>Earned</span></h2></div>'.
    '<div class="exc-box"><div class="wrap_bt"><span class="num">'. $_SESSION['user_orig_exc'] .'</span><br /><span>Excelonz</span></div></div>'.
    //'<br/>Session Excellonz : ' . $_SESSION['user_session_exc'] .
    '<div class="play-label-title" style="display:none">
      <h2 class="left"><a href="#">Play Off Started</a></h2>
    </div>'.
    $level_markup .$revision_markup.
    '<div class="correct-ans">' . $_SESSION['correct_ans'] .'</div>'.
    '<div class="wrong-ans">' . $_SESSION['wrong_ans'] .'</div>'.
    //'<br/>' . $_SESSION['level_wrong_ans'] .

    '</div>'.
      '<div class="left_ex_block">
        <div id="question_area">
          <div class="question_title">
            <h2><span>Question:</span>'.$node->title.'</h2>
          </div>
          <div class="question-div-blk">'.$img_with_txt.
            '<div class="question-text">
              <div class="question_div">
                <h3>' . $node->field_question_text['und'][0]['value'] . '</h3>
              </div>
            </div>
          </div>
        </div>' .
        '<div class="hlptxt">Choose an answer below :</div>'.
      '<div class="mcq_ext_blk">
        <div class="question_wrap">'.$opt.'</div>
        <div class="answer_link '.$n_type.'">'.$ans_desc_link.'</div>
      </div>
      <div class="desc_wrap mcqndtf '.$n_type.'">'.$ans_desc_link.'</div></div>',
    '#suffix' =>  '</div><script>level_change_txt("'.$level_msg.'")</script></div>',
  );

  //@todo : prateek code cleanup.
  if ($n_type == 'fib') {
    $form['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="option-list" class="fib_quest '.$arg_value.'">',
      '#markup' =>  $question_level_print .
     '<div class="right_exl_block '.$n_type.'">
        <div class="session_ex2">
          <h2>'.$name.'<span>Earned</span></h2>
        </div>'.
        '<div class="exc-box">
          <div class="wrap_bt">
            <span class="num">'. $_SESSION['user_orig_exc'] .'</span><br />
            <span>Excelonz</span>
          </div>
        </div>'.
    '<div class="play-label-title" style="display:none">
      <h2 class="left"><a href="#">Play Off Started</a></h2>
        </div>'.
        $level_markup .$revision_markup.
        '<div class="correct-ans">' . $_SESSION['correct_ans'] .'</div>'.
        '<div class="wrong-ans">' . $_SESSION['wrong_ans'] .'</div>'.
      '</div>'.
      '<div class="left_ex_block">
        <div id="question_area">
          <div class="question_title">
            <h2><span>Question:</span>'.$node->title.'</h2>
          </div>
          <div class="question-div-blk">'.$img_with_txt.
            '<div class="question-text">
              <div class="question_div">
                <h3>' . $question_title_val . '</h3>
              </div>
            </div>
          </div>
        </div>' .
        '<div class="hlptxt">Fill in the blanks :</div>'.
        '<div class="fib_ext_blk">
          <div class="question_wrap">'.$opt.'</div>
          <div class="answer_link fib">'.$ans_desc_link.'</div>
        </div>
        <div class="fib_wrap">
          <div class="desc_wrap fib"></div>
        </div>
      </div>',
    '#suffix' => '<script>level_change_txt("'.$level_msg.'")</script></div>',
  );
  }
  // For Jumble and unjumbled question type
  if ($n_type == 'jumble') {
    $question_title_val = $node->field_question_text['und'][0]['value'];
    $form['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="option-list" class="jumble_div">',
      '#markup' =>  //$question_level_print .
      '<div class="right_exl_block '.$n_type.'">
        <div class="session_ex2">
          <h2>'.$name.'<span>Earned</span></h2>
        </div>
        <div class="exc-box">
          <div class="wrap_bt">
            <span class="num">'. $_SESSION['user_orig_exc'] .'</span><br />
            <span>Excelonz</span>
          </div>
        </div>
    <div class="play-label-title" style="display:none">
      <h2 class="left"><a href="#">Play Off Started</a></h2>
        </div>'.
        $level_markup .'
        <div class="correct-ans">' . $_SESSION['correct_ans'] .'</div>
        <div class="wrong-ans">' . $_SESSION['wrong_ans'] .'</div>
      </div>
      <div class="left_ex_block">
        <div class="jumble_question_wrap">
          <div class="question_title">
            <h2><span>Question:</span>'.$node->title.'</h2>
          </div>
          <div class="question-div-blk jumble">'.$img_with_txt.
            '<div class="question-text">
              <div class="question_div">
                <h3>' . $question_title_val . '</h3>
              </div>
            </div>
          </div>' .
          $jumble_wrap .'
        </div>
        <div class="jques">
          <h2><span>Drag your answer here</span></h2>
        </div>
        <div class="drag-area jumbd">
          <div class="extra-area">
            <ol class="box-area placeholder"></ol>
            <div class="jumbtxt">Clear Text</div>
          </div>
          <textarea class="drag" style="display:none" >'.$default_text.'</textarea>
          <div class="current current_entry">User Input</div>
          <div class="answer_link jumble">'.$ans_desc_link.'</div>
        </div>
        <div class="desc_wrap jumb"></div>
        <div class="jumble_answer_input">
          <div class="default_box">
            <textarea id ="dragtxt" name= "opt" class="give_val" style="display:none" ></textarea>
          </div>
        </div>
      </div>',
      '#suffix' => '<script>level_change_txt("'.$level_msg.'")</script></div><div class="scr"><script>drag_drop();</script></div>',
    );
  }

  // For Match the Following question type
  if ($n_type == 'match_the_following') {
    $question_title_val = $node->field_question_text['und'][0]['value'];
    $form['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="option-list" class="opt" ><div id="option-list-match">',
      '#markup' =>  //$question_level_print .
      '<div class="right_exl_block '.$n_type.'"><div class="session_ex2"><h2>'.$name.'<span>Earned</span></h2></div>'.
     '<div class="exc-box"><div class="wrap_bt"><span class="num">'. $_SESSION['user_orig_exc'] .'</span><br /><span>Excelonz</span></div></div>'.
    '<div class="play-label-title" style="display:none">
      <h2 class="left"><a href="#">Play Off Started</a></h2>
    </div>'.
    $level_markup .
    '<div class="correct-ans">' . $_SESSION['correct_ans'] .'</div>'.
    '<div class="wrong-ans">' . $_SESSION['wrong_ans'] .'</div>'.
    '</div>'.
      '<div class="left_ex_block">
        <div class="main_qs_area">
          <div class="question_title">
            <h2><span>Question:</span>'.$node->title.'</h2>
            <div class="jques">
              <h2><span>Drag your answer here</span></h2>
            </div>
          </div>
          <div class="question-text">
              <div class="question_div">
                <h3 style="display: block;float:left;width:100%;">' . $question_title_val . '</h3>
              </div>
            </div>
          <div class="match_blk">
            <div class="match_question_wrap">' . $match_question_wrap . '</div>
            <div class="match_ans_wrap">'. $match_ans_wrap .'</div>
            <div class="answer_link match">'.$ans_desc_link.'</div>
            <div class="mtfclear">Clear</div>
          </div>
          <div class="desc_wrap jumb match"></div>
          <div class="default_box">
            <div class="actual_word" style="display:none">'.$correct_match.'</div>
            <textarea id ="dragtxt" name= "opt" class="give_val" style="display:none" ></textarea>
          </div>
      </div>',
      '#suffix' => '<script>level_change_txt("'.$level_msg.'")</script></div></div><div class="scr" style="display:none"><script>drag_drop();</script></div></div>',
    );
  }


  return $form;
}


/**
 * Function to process current level and return question level of difficulty accordingly.
 * See the document of level of difficulty for more detail.
 * @param type $level
 * @return type
 */
function get_current_question_level($level) {
  global $user;
  $uid = $user->uid;
  //get tid
  $tid = $_SESSION['topic_tid'];
  $duration = $_SESSION['timer_value'];
  //echo $tid;
  //check for fist time.
  if (!array_key_exists('question_lod', $_SESSION)) {
    update_lod_down_session();
    $_SESSION['question_lod'] = 0;
    $_SESSION['level_name'] = '';
  }


    if (strpos($_SESSION['level_up'],'Congrats') !== false) {
         $_SESSION['level_up'] = 'not_started';
    }

  //@todo : store upgraded level
  //check for lod
  if ($level == 1 && $_SESSION['level_correct_ans'] == 15) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 50;
    $_SESSION['user_session_exc'] += 50;
    $_SESSION['level_up'] = "Congrats,<br/>  You reached LEVEL 2!";


  }
  elseif ($level == 2 && $_SESSION['level_correct_ans'] == 15) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 100;
    $_SESSION['user_session_exc'] += 100;
    $_SESSION['level_up'] = "Congrats,<br/>  You reached LEVEL 3!";
  }
  elseif ($level == 3 && $_SESSION['level_correct_ans'] == 15) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 200;
    $_SESSION['user_session_exc'] += 200;

    $query1 = new EntityFieldQuery();
     $query1->entityCondition('entity_type', 'badges2')
      ->propertyCondition('uid', $uid)
      ->propertyCondition('badge_name', 'covered')
      ->fieldCondition('field_termid', 'tid', $tid)
      ->range(0, 1);
    $result1 = $query1->execute();
    if(!isset($result1['badges2'])) {

      $entity = entity_create("badges2",
        array('uid' => $uid,
        'badge_name' => 'covered',
        'type' => 'user',
        'timestamp' => time(),
        'field_termid' => array(
          LANGUAGE_NONE => array(
            0 => array(
              'tid' => $tid,
            ),
          ),
        ),
      ));
      $en = entity_save("badges2", $entity);
    }

    $_SESSION['level_up'] = "Congrats, You learned this Topic!";
    $_SESSION['cover'] = true;

  }
  elseif ($level == 4 && $_SESSION['level_correct_ans'] == 15) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 300;
    $_SESSION['user_session_exc'] += 300;
    $_SESSION['level_up'] = "Congrats,<br/>  You reached LEVEL 5!";
  }
  elseif ($level == 5 && $_SESSION['level_correct_ans'] == 15) {
    //@todo : ask for scenarion when level 5 complete.
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 400;
    $_SESSION['user_session_exc'] += 400;

    $query1 = new EntityFieldQuery();
     $query1->entityCondition('entity_type', 'badges2')
      ->propertyCondition('uid', $uid)
      ->propertyCondition('badge_name', 'mastered')
      ->fieldCondition('field_termid', 'tid', $tid)
      ->range(0, 1);
    $result1 = $query1->execute();

    if(!isset($result1['badges2'])) {
      $entity = entity_create("badges2",
            array('uid' => $uid,
              'badge_name' => 'mastered',
              'type' => 'user',
              'timestamp' => time(),
              'field_termid' => array(
                LANGUAGE_NONE => array(
                  0 => array(
                  'tid' => $tid,
                 ),
                ),
          ),
      ));
      $en = entity_save("badges2", $entity);
    }



     $_SESSION['level_up'] = "Congrats! You Mastered this topic!";

    $_SESSION['master'] = true;
  }

  if ($level != $_SESSION['user_current_level']) {
    //global $user;
    $level = $_SESSION['user_current_level'];


      $total1 = $_SESSION['correct_ans'] + $_SESSION['wrong_ans'];
      $total_c1 = $_SESSION['correct_ans'];

        if(!array_key_exists('prev_total', $_SESSION)) {
          $_SESSION['prev_total'] = 0;
          $_SESSION['prev_total_c'] = 0;
        }

      $total = $total1 - $_SESSION['prev_total'];
      $total_c = $total_c1 - $_SESSION['prev_total_c'];
      $_SESSION['prev_total'] = $total1;
      $_SESSION['prev_total_c'] = $total_c1;

    //store users level;
    $query1 = new EntityFieldQuery();
    $query1->entityCondition('entity_type', 'user_info')
      ->propertyCondition('uid', $user->uid)
      ->propertyCondition('topic_id', $tid)
      ->range(0, 1);
    $result1 = $query1->execute();
      $ui_ids = array_keys($result1['user_info']);
      $ui_id = $ui_ids[0];
      $ui_info = entity_load_single("user_info", $ui_id);

      //$ui_info->totaltime
      $ui_info->totaltime =$ui_info->totaltime  + $duration;
      $ui_info->level = $level;
      $ui_info->totalq = $ui_info->totalq + $total;
      $ui_info->correcta = $ui_info->correcta + $total_c;


      $en = entity_save('user_info', $ui_info);

      update_lod_down_session();


      /* save it in user_level */


      $entity = entity_create("user_level",
      array(
        'uid' => $user->uid,
        'type' => 'user',
        'level' => $level,
        'topic_tid' => $_SESSION['topic_tid'],
        'total' => $total,
        ));
      $en = entity_save('user_level', $entity);



      //save excellone to user profile

    $account = user_load($user->uid);
    $edit = array(
      'field_excellone' => array(
        'und' => array(
          0 => array(
            'value' => $_SESSION['user_orig_exc'],
          ),
        ),
      ),
    );
    user_save($account, $edit);

    $_SESSION['level_correct_ans'] = 0;

  }

  //check for question level
  if ($level == 1) {
    if ($_SESSION['question_lod'] == 5) {
      $_SESSION['level_name'] = "Easy";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['question_lod'] == 3 && $_SESSION['level_name'] == "Easy") {
      $_SESSION['level_name'] = "Very Easy";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['level_name'] != "Easy") {
      $_SESSION['level_name'] = "Very Easy";
    }
    $_SESSION['question_lod']++;
  }
  elseif ($level == 2) {
    if ($_SESSION['question_lod'] == 5) {
      $_SESSION['level_name'] = "Very Easy";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['question_lod'] == 3 && $_SESSION['level_name'] == "Very Easy") {
      $_SESSION['level_name'] = "Easy";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['level_name'] != "Very Easy") {
      $_SESSION['level_name'] = "Easy";
    }

    $_SESSION['question_lod']++;
  }
  elseif ($level == 3) {
    if ($_SESSION['question_lod'] == 5) {
      $_SESSION['level_name'] = "Easy";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['question_lod'] == 3 && $_SESSION['level_name'] == "Easy") {
      $_SESSION['level_name'] = "Difficult";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['level_name'] != "Easy") {
      $_SESSION['level_name'] = "Difficult";
    }

    $_SESSION['question_lod']++;
  }
  elseif ($level == 4) {
    if ($_SESSION['question_lod'] == 5) {
      $_SESSION['level_name'] = "Very Difficult";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['question_lod'] == 3 && $_SESSION['level_name'] == "Very Difficult") {
      $_SESSION['level_name'] = "Difficult";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['level_name'] != "Very Difficult") {
      $_SESSION['level_name'] = "Difficult";
    }

    $_SESSION['question_lod']++;
  }
  elseif ($level == 5) {
    if ($_SESSION['question_lod'] == 5) {
      $_SESSION['level_name'] = "Difficult";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['question_lod'] == 3 && $_SESSION['level_name'] == "Difficult") {
      $_SESSION['level_name'] = "Very Difficult";
      $_SESSION['question_lod'] = 0;
    }
    elseif ($_SESSION['level_name'] != "Difficult") {
      $_SESSION['level_name'] = "Very Difficult";
    }


    $_SESSION['question_lod']++;
  }
  elseif($level == 6) {
      $level_name_array = array("Easy", "Very Easy", "Difficult", "Very Difficult");
      $_SESSION['level_name'] = $level_name_array[array_rand($level_name_array, 1)];
  }
  $level_tid = taxonomy_get_term_by_name($_SESSION['level_name']);
  //@todo : use array_keys instead of foreach
  foreach ($level_tid as $lid) {
    $question_level_tid = $lid->tid;
  }
  return $question_level_tid;
}


/**
 * page to display list of topic based on argument of parent term id.
 */
function assessment_get_topic() {

  if (!array_key_exists('tid', $_GET)) {
    return 'Argument not found';
  }
  else {
    $parent_tid = $_GET['tid'];
  }
  $child_topics = taxonomy_get_children($parent_tid);
  $output = "<table><tr>";
  $counter = 1;
  foreach ($child_topics as $topic) {
    $output .= "<td>";
    if (array_key_exists('und', $topic->field_image)) {
      $image =  $topic->field_image['und']['0']['filename'];
      $output .= "<span>" . l(theme_image_style(array('style_name' => 'course_thumb', 'path' => $image, 'width' => '', 'height' => '')),
          'assessments/take', array('html' => TRUE, 'query' => array("tid" => $topic->tid, "ptid" => $parent_tid))) . "</span>";
    }
    $output .= "<span>" . l($topic->name, 'assessments/take', array('query' => array("tid" => $topic->tid, "ptid" => $parent_tid))) . "</span></td>";
    if ($counter%3 == 0) {
      $output .= "</tr><tr>";
    }
    $counter++;
  }
  $output .= '</tr></table>';
  return $output;
}


/*
 * @todo : Add comment
 */
function update_lod_down_session() {
  if ($_SESSION['user_current_level'] == 2)
    $_SESSION['level_wrong_ans'] = 2;
  elseif ($_SESSION['user_current_level'] == 3)
    $_SESSION['level_wrong_ans'] = 4;
  elseif ($_SESSION['user_current_level'] == 6)
    $_SESSION['level_wrong_ans'] = 400;
  else
    $_SESSION['level_wrong_ans'] = 3;
}


/**
 *  @todo : Add comment
 */
function downgrade_lod() {
  $tid = $_SESSION['topic_tid'];;

  //@todo : add filter of subject and topic

  global $user;
  $query1 = new EntityFieldQuery();
  $query1->entityCondition('entity_type', 'user_info')
    ->propertyCondition('uid', $user->uid)
    ->propertyCondition('topic_id', $tid)
    ->range(0, 1);

  $result1 = $query1->execute();
    $ui_ids = array_keys($result1['user_info']);
    $ui_id = $ui_ids[0];


      $total1 = $_SESSION['correct_ans'] + $_SESSION['wrong_ans'];
      $total_c1 = $_SESSION['correct_ans'];
      $total = $total1 - $_SESSION['prev_total'];
      $total_c = $total_c1 - $_SESSION['prev_total_c'];
      $_SESSION['prev_total'] = $total1;
      $_SESSION['prev_total_c'] = $total_c1;


    $ui_info = entity_load_single("user_info", $ui_id);

    $ui_info->level--;
    $ui_info->totalq = $ui_info->totalq + $total;
    $ui_info->correcta = $ui_info->correcta+ $total_c;

    $temp_level =$ui_info->level;
    $en = entity_save('user_info', $ui_info);

    //downgrade
    $_SESSION['level_up'] = "OOPS you are back to Level" . $temp_level;
    //$_SESSION['level_up'] = "Sorry Downgrade to Previous level";
    /* save it in user_level */

      /* save it in user_level */


      $cur_level =$_SESSION['user_current_level'] - 1;
      $entity = entity_create("user_level",
      array(
        'uid' => $user->uid,
        'type' => 'user',
        'level' => $cur_level,
        'topic_tid' => $_SESSION['topic_tid'],
        'total' => $total,
        ));
      $en = entity_save('user_level', $entity);


$_SESSION['user_current_level']--;
$_SESSION['level_correct_ans'] = 0;
    update_lod_down_session();
}



/**
 * called to store skillmap
 * @param  [type] $nid     [description]
 * @param  [type] $correct [description]
 * @return [type]          [description]
 */
function skillmap_record($nid, $correct, $subject_tid) {
  global $user;
  $uid = $user->uid;

  //fetch all skillmap tid for current nid
  //loop
  //  check skillmap exist or not
  //  if not exist
  //    if correct ans
  //      store correct as 1
  //     else
  //      store wrong as 1
  //     endif
  //  endif
  //
  //  if exist update the number
  //end loop
  //
$debug = 'nodeid = ' . $nid;

  $skill_query = db_select('field_data_field_skills', 's')
        ->fields('s')
        ->condition('entity_id', $nid)
        ->condition('entity_type', 'node')
        ->execute()
        ->fetchAll();

  foreach ($skill_query as $value) {
    $tid = $value->field_skills_tid;
$debug .= "tid - " . $tid;

    $skillmap_search = db_select('eck_skillmap', 's')
        ->fields('s')
        ->condition('uid', $uid)
        ->condition('tid', $tid)
        ->range(0, 1)
        ->execute()
        ->fetchAssoc();

    if(array_key_exists('id', $skillmap_search)) {
  $debug .= "exist";

      if($correct == TRUE) {
        $debug .= "corrrect - " . $value->correct;
        $total = $skillmap_search['correct'] + 1;
        $num_updated = db_update('eck_skillmap')
          ->fields(array(
          'correct' => $total,
        ))
        ->condition('uid', $uid)
        ->condition('tid', $tid)
        ->execute();
      }
      else {
        $debug .= "wrong" . $value->wrong;
        $total = $skillmap_search['wrong'] + 1;
        $num_updated = db_update('eck_skillmap')
          ->fields(array(
          'wrong' => $total,
        ))
        ->condition('uid', $uid)
        ->condition('tid', $tid)
        ->execute();
      }

    }
    else {
      $debug .= "not found";
      if($correct == TRUE) {
        $entity = entity_create("skillmap",
        array(
          'uid' => $uid,
          'type' => 'user',
          'tid' => $tid,
          'correct' => 1,
          'wrong' => 0,
          'subject_tid' => $subject_tid
          ));
        $en = entity_save('skillmap', $entity);
      }
      else {
        $entity = entity_create("skillmap",
        array(
          'uid' => $uid,
          'type' => 'user',
          'tid' => $tid,
          'correct' => 0,
          'wrong' => 1,
          'subject_tid' => $subject_tid
          ));
        $en = entity_save('skillmap', $entity);
      }
    }
  }
  //echo $debug;die();
}

function is_free_subscription() {
  global $user;
  $uid = $user->uid;

  $paid_check = db_select('eck_expiry', 'ee');
  $paid_check->fields("ee")
    ->condition('child_id', $uid)
    ->condition('purchase_type', 'paid');
  $paid_count = $paid_check->execute()->rowCount();
  if($paid_count > 0 ) {
    return false;
  }
  else {
    $free_check = db_select('eck_expiry', 'ee');
    $free_check->fields("ee")
      ->condition('child_id', $uid)
      ->condition('purchase_type', 'free');
    $free_count = $free_check->execute()->rowCount();
    if($free_count > 0 ) {
      return true;
    }
    else {
      return false;
    }
  }
}

function get_free_subscription_form($call= "first") {
  $level_markup = '<div class="label-bg"><ul class="label">' ;
    for ($i = 1 ; $i<6 ; $i++) {
      if($i <= $_SESSION['user_current_level']) {
        $class_text = 'label-over-'.$i;
      }
      else {
        $class_text = 'label-'.$i;
      }
      $level_markup .=  '<li class="'.$class_text.'"><span>'.$i.'</span></li>';
    }
    $level_markup .= "</ul>";
    $level_markup .= '<div class="label-text">levels';
    $level_markup .= "</div></div>";

    $output .= '<div class="freeleveltext">Kindly buy a subscription to continue practicing this topic, alternatively you can try and experience other topics</div>';
    $output .= '<div class="right_exl_block mcqndtf '.$arg_value.'"><div class="session_ex2"><h2>'.$_SESSION['name'].'<span>Earned</span></h2></div>';
    $output .= '<div class="exc-box"><div class="wrap_bt"><span class="num">'. $_SESSION['user_orig_exc'] .'</span><br/>
                <span>Excelonz</span></div></div>';
    $output .= $level_markup;
    $output .= '<div class="correct-ans">' . $_SESSION['correct_ans'] .'</div>'.
               '<div class="wrong-ans">' . $_SESSION['wrong_ans'] .'</div>';
    $output .= '</div>';


    if($call == "first") {
      $form1['timer_value'] = array(
        '#type' => 'textfield',
        '#title' => t('timer_value'),
        '#size' => 10,
        '#maxlength' => 128,
      );
      $form1['timer'] = array(
        '#type' => 'markup',
        '#markup' => '<div class="timer"><span class="startstoptime">0:00</span><p>mins spent</p></div>',
        '#weight' => -102,
      );

      $topic = taxonomy_term_load($_SESSION['topic_tid']);
      $parents = taxonomy_term_load($_SESSION['subject_tid']);
      //echo '<pre>';print_r($node);die();
      $topic_name = $topic->name;
      $subject_name = $parents->name;
      $form1['head'] = array(
        '#type' => 'markup',
        '#markup' => '<div class= "assessment-header-top"><h3 class= "assessment-header">'.$subject_name." : ".$topic_name.'</h3></div><div class="assessment_wrap">',
        '#weight' => -109,
      );
    }
    $form1['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="free_sub_ass_msg">',
      '#markup' => $output,
      '#suffix' => '</div>',
    );
    if($call == "first") {
      $form1['finish'] = array(
        '#type' => 'button',
        '#value' => 'Finish',
      );
    }
    return $form1;
}
