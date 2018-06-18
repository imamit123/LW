<?php
/**
 * @file
 *
 */

require_once ( dirname(__FILE__) . '/../assessments/assessments.inc');


/**
 *  Function to generate the form.
 *  This function will call for the first time when assessment is started.
 *  Steps
 *    - Generate random question Id.
 *    - Generate form structure.
 */
function lw_revision_form($form, &$form_state) {

  global $user;
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

  drupal_add_js('http://code.jquery.com/jquery-1.4.4.min.js'); // prateek
  drupal_add_js('http://code.jquery.com/jquery-1.7.2.min.js'); // prateek
  drupal_add_js('http://code.jquery.com/ui/1.8.21/jquery-ui.min.js'); // prateek

  //Query to fetch time
  $duration_fetch = db_select('eck_revision', 'r')
    ->fields('r')
    ->condition('tid', $_GET['tid'])
    ->condition('uid', $user->uid)
    ->condition('status', 1)
    ->range(0, 1)
    ->execute()
    ->fetchall();

  $duration = $duration_fetch[0]->duration;
  $_SESSION['set_time'] = $duration;

  //limit the total no of question for the specific duration
  $_SESSION['current'] = 1;
  if($duration == 10) {
    $_SESSION['max'] = 15;
  }
  elseif($duration == 15) {
    $_SESSION['max'] = 20;
  }
  elseif($duration == 20) {
    $_SESSION['max'] = 30;
  }
  elseif($duration == 30) {
    $_SESSION['max'] = 40;
  }


  //@todo : move js to the type where it is required.
  drupal_add_js( drupal_get_path('module', 'assessments') . '/assessments.js');
  drupal_add_js( drupal_get_path('module', 'assessments') . '/timer.js');


  drupal_add_js(array(
    'revision_time' => array(
      'duration' => $duration ,
     ),
    ),
  'setting');
  drupal_add_js( drupal_get_path('module', 'lw_revision') . '/lw_revision.js');



  drupal_add_css( drupal_get_path('module', 'assessments') . '/assessments.css');
  drupal_add_js( drupal_get_path('module', 'assessments') . '/jquery.ui.touch-punch.min.js');// prateek


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
    }
    $_SESSION['timer_value'] = $_POST['timer_value'];

    drupal_goto('revision-report');
  }
  else {
    unset($_SESSION['report_id']);
    $_SESSION['correct_ans'] = 0;
    $_SESSION['wrong_ans'] = 0;
  }
  unset($_SESSION['qid']);

    $qid = lw_revision_random_question();
    $_SESSION['qid'] = $qid;


  if($duration == 600) {
    $_SESSION['revision']['time'] = "unlimited";
    $extra_css = 'style="display:none;';
  }
  else {
    $_SESSION['revision']['time'] = "limited";
  }

  $form = assessment_generate_form($qid);

  global $base_url;
  //@todo : do not user node load fetch node type with query.
  $node = node_load($qid);
  $n_type = $node->type;
  $form['timer_value'] = array(
    '#type' => 'textfield',
    '#title' => t('timer_value'),
    '#size' => 10,
    '#maxlength' => 128,
  );
  if($duration == 600) {
    $_SESSION['revision']['time'] = "unlimited";
    $extra_css = 'style="display:none;';
  }
  else {
    $_SESSION['revision']['time'] = "limited";
  }

  $form['timer'] = array(
    '#type' => 'markup',
    '#markup' => '<div '.$extra_css.' class="timer"><span class="revisiontime">'.$duration.':00</span><p>mins left</p></div>',
    '#weight' => -110,
  );
  $form['sure'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="btn-wrap '.$n_type.'"><div class="btn-wrap-inner"><p class="sure">Are You Sure</p>',
  );
  $form['sub'] = array(
    '#type' => 'markup',
    '#markup' => '<button id="submit-button" type="button">Yes</button> ',
  );
  $form['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<button id="reset" type="button">No</button></div></div>',
  );
  $form['action']['next'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'lw_revision_next',
      'wrapper' => array('option-list'),
      'name' => 'next',
    ),
    '#value' => t('Next'),
  );
  $form['finish'] = array(
    '#type' => 'button',
    '#value' => 'Finish',
     '#weight' => -109,
  );

  //@todo : fetch it with query not term_load.
  $topic = taxonomy_term_load($_SESSION['topic_tid']);
  $parents = taxonomy_term_load($_SESSION['subject_tid']);

  $topic_name = $topic->name;
  $subject_name = $parents->name;
  $form['head'] = array(
    '#type' => 'markup',
    '#markup' => '<h3 class= "assessment-header">'.$subject_name." : ".$topic_name.'</h3>',
    '#weight' => -109,
  );

  return $form;
}


/**
 * This function will call when next button will be clicked.
 */
function lw_revision_next($form, $form_state) {

  if ($_POST['opt'] == "Correct") {
    $_SESSION['correct_ans']++;
    $_SESSION['level_correct_ans']++;
    $_SESSION['level_wrong_ans'] = 0;
    $_SESSION['user_orig_exc']++;
    $_SESSION['user_session_exc']++;

  }
  else {
    $_SESSION['wrong_ans']++;
    $_SESSION['level_wrong_ans']--;
    if ($_SESSION['level_wrong_ans'] == 0 && $_SESSION['user_current_level'] != 1) {
        $_SESSION['level_correct_ans'] = 0;
        $_SESSION['user_current_level']--;
        update_lod_down_session();
    }
  }

  $qid = lw_revision_random_question();
  $_SESSION['qid'] = $qid;

  $_SESSION['current']++;
  if($_SESSION['current'] == $_SESSION['max']) {
    $qid = '';
  }
  if ($qid == '') {
    $form1['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="option-list"><br/>',
      '#markup' => '<div class="no_more_ques"><img src="/sites/default/files/field/image/no_more_ques_0.jpg"/></div>',
      '#suffix' => '</div>',
    );
  }
  else {
    $form1 = assessment_generate_form($qid);
  }

  return $form1;
}


/**
 * function to select random question
 */
function lw_revision_random_question() {
  global $user;
  $uid = $user->uid;

  //call this function for the fist time only.
  if (!array_key_exists('user_class_value', $_SESSION)) {

    $_SESSION['start_time'] = time();
    $_SESSION['level_wrong_ans'] = 0;

 //fetch users profile ID.
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

    //for revision start from level 1
    $level = 1;

    $class = $result['name'];

    $_SESSION['class'] = $result['tid'];
    $_SESSION['user_class_value'] = $class;
    $_SESSION['user_current_level'] = $level;

    $_SESSION['level_correct_ans'] = 0;
    $user1 = user_load($uid);
    $_SESSION['user_orig_exc'] = $user1->field_excellone['und'][0]['value'];
    $_SESSION['user_session_exc'] = 0;
  }


  $question_level_id = lw_revision_get_current_question_level($_SESSION['user_current_level']);

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
    //$_SESSION['class'] = $class_term_id;
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
 * page to display list of topic based on argument of parent term id.
 */
function lw_revision_get_topic() {

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

/**
 * Function to process current level and return question level of difficulty accordingly.
 * See the document of level of difficulty for more detail.
 * @param type $level
 * @return type
 */

function lw_revision_get_current_question_level($level) {
  global $user;
  $uid = $user->uid;
  //get tid
  $tid = $_SESSION['topic_tid'];;
  //check for fist time.
  if (!array_key_exists('question_lod', $_SESSION)) {
    update_lod_down_session();
    $_SESSION['question_lod'] = 0;
    $_SESSION['level_name'] = '';
  }
  //@todo : store upgraded level
  //check for lod
  if ($level == 1 && $_SESSION['level_correct_ans'] == 5) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 25;
    $_SESSION['user_session_exc'] += 25;
  }
  elseif ($level == 2 && $_SESSION['level_correct_ans'] == 5) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 25;
    $_SESSION['user_session_exc'] += 25;
  }
  elseif ($level == 3 && $_SESSION['level_correct_ans'] == 5) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 50;
    $_SESSION['user_session_exc'] += 50;
  }
  elseif ($level == 4 && $_SESSION['level_correct_ans'] == 5) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 150;
    $_SESSION['user_session_exc'] += 150;
  }
  elseif ($level == 5 && $_SESSION['level_correct_ans'] == 5) {
    $_SESSION['user_current_level']++;
    $_SESSION['user_orig_exc'] += 100;
    $_SESSION['user_session_exc'] += 100;
  }

  if ($level != $_SESSION['user_current_level']) {
    global $user;
    $level = $_SESSION['user_current_level'];
    $_SESSION['level_correct_ans'] = 0;

      update_lod_down_session();

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
  $level_tid = taxonomy_get_term_by_name($_SESSION['level_name']);
  //@todo : use array_keys instead of foreach
  foreach ($level_tid as $lid) {
    $question_level_tid = $lid->tid;
  }
  return $question_level_tid;
}
