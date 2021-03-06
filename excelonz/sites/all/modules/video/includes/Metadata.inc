<?php
/**
 * @file
 * Class file used to store metadata on the video.
 */

class Metadata {
  private $metadata;

  public function __construct($metadata = NULL) {
    // get our configured transcoder.
    if (!isset($metadata))
      $metadata = variable_get('video_metadata', 'flvtool2');
    if (!module_load_include('inc', 'video', '/metadata/' . $metadata)) {
      $modules = module_list();
      foreach ($modules as $module) {
        $mobule_files = array();
        $module_path = drupal_get_path('module', $module) . '/metadata';
        $mobule_files = file_scan_directory($module_path, '/.*\.inc/');
        if (is_array($mobule_files)) {
          foreach ($mobule_files as $file) {
            if ($file->name == $metadata)
              require_once $file->filename;
          }
        }
      }
    }
    if (class_exists($metadata)) {
      $this->metadata = new $metadata;
    }
    else {
      drupal_set_message(t('The metadata is not configured properly.'), 'error');
    }
  }

  public function process($video) {
    $command_output = $this->metadata->process($video);
    return $command_output;
  }

  public function adminSettings() {
    $form = array();
    $form['video_metadata'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Metadata'),
      '#default_value' => variable_get('video_metadata', FALSE),
      '#description' => t('Metadata is particularly useful in video, where content information (such as conversation transcripts or scene descriptions) are not directly accessible by a computer, but where searchability is desired.'),
    );
    $options = $this->_metadata();
    $form['video_metadata'] = array(
      '#type' => 'radios',
      '#title' => t('Video Metadata'),
      '#default_value' => variable_get('video_metadata', 'flvtool2'),
      '#options' => $options['radios'],
      '#description' => t('!list', array('!list' => theme('item_list', $options['help']))),
      '#prefix' => '<div id="metadata-radios">',
      '#suffix' => '</div>',
    );
    $form = $form + $options['admin_settings'];
    $form['video_metadata_dimensions'] = array(
      '#type' => 'textarea',
      '#title' => t('Available Dimensions for uploaded videos'),
      '#description' => t('Enter one set of Video Resolution dimensions (for example 1280x720) per line.'),
      '#default_value' => variable_get('video_metadata_dimensions', video_utility::getDefaultDimensions()),
      '#required' => TRUE,
    );

    return $form;
  }

  private function _metadata() {
    $files = array();
    // Lets find our transcoder classes and build our radio options
    // We do this by scanning our transcoders folder
    $form = array('radios' => array(), 'help' => array(), 'admin_settings' => array());
    $path = drupal_get_path('module', 'video') . '/metadata';
    $files = file_scan_directory($path, '/.*\.inc/');
    // check inside sub modules
    $modules = module_list();
    foreach ($modules as $module) {
      $mobule_files = array();
      $module_path = drupal_get_path('module', $module) . '/metadata';
      $mobule_files = file_scan_directory($module_path, '/.*\.inc/');
      $files = array_merge($files, $mobule_files);
    }

    foreach ($files as $file) {
      if (!module_load_include('inc', 'video', '/metadata/' . $file->name))
        require_once $file->filename;
      $focus = new $file->name;
      $form['radios'][$file->name] = $focus->getName();
      $form['help'][] = $focus->getHelp();
      $form['admin_settings'] = $form['admin_settings'] + $focus->adminSettings();
    }
    return $form;
  }

  public function adminSettingsValidate($form, &$form_state) {
    $v =& $form_state['values'];
    if (!empty($v['video_metadata_dimensions'])) {
      $v['video_metadata_dimensions'] = str_replace("\r", '', $v['video_metadata_dimensions']);
      if (!video_utility::validateDimensionList($v['video_metadata_dimensions'])) {
        form_error($form['video_metadata_dimensions'], t('The list of dimensions contains errors: only enter new lines and dimensions in the form widthxheight.'));
      }
    }

    $this->metadata->adminSettingsValidate($form, $form_state);
  }
}

interface metadata_interface {

  public function getName();

  public function getHelp();

  public function process($video);

  public function adminSettings();

  public function adminSettingsValidate($form, &$form_state);
}
