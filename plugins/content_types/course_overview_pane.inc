<?php

/**
 * @file
 * Define a ctools plugin to D1 course section displays (right rail section list).
 *
 * See constants .inc file. 
 */

/**
 * Define Plugin.
 */
 $plugin = array(
  'title'           => t('Course Node Overview Pane'),
  'single'          => FALSE,
  'description'     => t('Course overview from from D1 API.'),
  'category'        => array('UNH DestinyOne'),
  'all contexts'    => TRUE,
  'edit form'       => 'course_overview_pane_content_type_edit_form',
  'render callback' => 'course_overview_pane_content_type_render',
);
 
/**
 * Title callback for admin page.
 */
function course_overview_pane_admin_title($subtype, $conf, $context = NULL) {
  return t('Course Node Overview Pane');
}
 
/**
 * Callback to provide administrative info (the preview in panels when building a panel).
 */
function course_overview_pane_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Course Overview Pane');
  $config = array();
  if ($conf['override_title'] == TRUE) {
    $title_value = '<b>' . $conf['override_title_text'] . '</b>';
  }
  else {
    $title_value = t('Not Set');
  }
  $config[] = t('Title') . ': ' . $title_value;
  $block->content = theme_item_list(array( 'items' => $config, 'title' => NULL, 'type' => 'ul', 'attributes' => array() ));
  return $block;
}
 
/**
 * Edit callback for the content type.
 */
function course_overview_pane_content_type_edit_form($form, &$form_state) {

  $conf = $form_state['conf'];
  
  return $form;
}
 
/**
 * Submit callback for settings form.
 */
function course_overview_pane_content_type_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
 
/**
 * Run-time rendering course sections pane (right-rail list of section blocks).
 */
 function course_overview_pane_content_type_render($subtype, $conf, $panel_args) {
  
  $block = NULL;
  $node = menu_get_object();
  
  if ($node->type == 'course') {
    $wrapper = entity_metadata_wrapper('node', $node);
    $course_code = $wrapper->field_course_code->value();
    $course = NULL;
    // $sections = array();
    // $courseId = 0;
    // $sectionIds = array();
    
    // Get course data.
    if (!empty($course_code)) {
      $information_level = 'full';
      $program_area = unh_d1_drupal_settings_program_area();
      
      $course = unh_d1_client_searchCourse_courseCode($course_code, array($program_area), $information_level);
      
      // if (!empty($course)) {
      //   $sections = unh_d1_client_searchCourseSections($course_code, array($program_area), $information_level);
        
      //   $courseId = unh_d1_client_getcourseObjectId($course);
      //   $sectionIds = unh_d1_client_getSectionArrayObjectIds($sections);
      // }
    }
    
    // Get config settings.
    $config = $conf;

    // Render the content with either theme() or by building a render array.
    $block = new stdClass();
    $block->content = array(
      // Render with theme() - example.
      // $args = array('course_nid' => '160', 'sections' => '20') + $panel_args;
      // '#markup' => theme('unh_d1_drupal__course_sections_pane', $args)
      // '#markup' => d1pdt_courseView_infoPane($panel_args[0])

      // Render with a render array - example.
      '#theme' => 'unh_d1_drupal__course_overview_pane',
      '#course_nid' => $node->nid,
      '#course' => $course,
      // '#sections' => $sections,
      '#config' => $config,
      /*
      '#attached' => array(
        'js'=> array(
          drupal_get_path('module', 'unh_d1_drupal') . '/js/unh_d1_drupal.sections_pane.js',
          array(
            'data' => array(
              'courseId' => $courseId,
              'sectionIds' => $sectionIds,
              'section_status' => 'SECTION IS AVAILABLE'
            ),
            'type' => 'setting',
          ),
        )
      )
      */
    );
  }
  
  return $block;
}