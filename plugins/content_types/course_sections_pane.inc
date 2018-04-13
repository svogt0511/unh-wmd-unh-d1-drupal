<?php

/**
 * @file
 * Define a ctools plugin to D1 course section displays.
 */

/**
 * Define Plugin.
 */
 $plugin = array(
  'title'           => t('Course Node Sections Pane'),
  'single'          => FALSE,
  'description'     => t('List of sections and their information.'),
  'category'        => array('UNH DestinyOne'),
  'all contexts'    => TRUE,
  'edit form'       => 'course_sections_pane_content_type_edit_form',
  'render callback' => 'course_sections_pane_content_type_render',
);
 
/**
 * Title callback for admin page.
 */
function course_sections_pane_admin_title($subtype, $conf, $context = NULL) {
  return t('Course Node Sections Pane');
}
 
/**
 * Callback to provide administrative info (the preview in panels when building a panel).
 */
function course_sections_pane_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->title = t('SKV Custom pane');
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
function course_sections_pane_content_type_edit_form($form, &$form_state) {

  $conf = $form_state['conf'];

  // the drupal checkboxes form field definition
  $form['action_button'] = array(
    '#title' => t('Action Button'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['action_button']) , 
  ); 
 
  $form['section_dates'] = array(
    '#title' => t('Section Dates'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_dates']) , 
  );
   
  $form['section_times'] = array(
    '#title' => t('Section Times'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_times']) , 
  );
 
  $form['section_locations'] = array(
    '#title' => t('Section Locations'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_locations']), 
  );
    
  $form['section_instructors'] = array(
    '#title' => t('Section Instructors'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_instructors']) , 
  ); 

  $form['section_tuition'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Section Tuition'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,  
  );

  $form['section_tuition']['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => (($form_state['op'] == 'add') ? "Cost:" : $conf['section_tuition']['label']) , 
  );

  $form['section_tuition']['displayPublishedCode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Published Cost Code'),
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_tuition']['displayPublishedCode']) , 
  );

  $form['section_contact_hours'] = array(
    '#title' => t('Section Contact Hours'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_contact_hours']) , 
  );

  $form['section_discounts'] = array(
    '#title' => t('Section Discounts'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_discounts']) , 
  );
  
  $form['section_notes'] = array(
    '#title' => t('Section Notes'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_notes']) , 
  );
  
  $form['section_ceus'] = array(
    '#title' => t('CEUs'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_ceus']) , 
  );
  
  $form['section_course_code'] = array(
    '#title' => t('Course Code'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_course_code']) , 
  );

  $form['section_number'] = array(
    '#title' => t('Section Number'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_number']) , 
  );
 
  return $form;
}
 
/**
 * Submit callback for settings form.
 */
function course_sections_pane_content_type_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
 
/**
 * Run-time rendering of the body of the block (content type).
 */
 function course_sections_pane_content_type_render($subtype, $conf, $panel_args) {
  
  $block = NULL;
  $node = menu_get_object();
  
  $body_section_fields = [];
  if ($node->type == 'course') {
    foreach($conf as $key => $value) {
      if (!empty($value)) {
        if (($key == 'action_button') ||
            ($key == 'section_times') ||
            ($key == 'section_locations') ||
            ($key == 'section_instructors') ||
            ($key == 'section_contact_hours') ||
            ($key == 'section_notes') ||
            ($key == 'section_ceus') ||
            ($key == 'section_course_code') ||
            ($key == 'section_number'))
        {
          $body_section_fields [] = $key;
        }
      }
    }

  
    // Render the content with either theme() or by building a render array.
    $block = new stdClass();
    $block->content = array(
      // Render with theme().
      // $args = array('course_nid' => '160', 'sections' => '20') + $panel_args;
      // '#markup' => theme('unh_d1_drupal__course_sections_pane', $args)
      // '#markup' => d1pdt_courseView_infoPane($panel_args[0])

      // Build a render array.
      '#theme' => 'unh_d1_drupal__course_sections_pane',
      '#course_nid' => $node->nid,
      '#sections' => '6',
      '#section_opt_1' => '900',
      '#body_section_fields' => $body_section_fields
    );
    
  }
  
  return $block;
  
/*  $block = new stdClass();
 
  if (isset($conf['nid'])) {
 
    $block = new stdClass();
    if ( $conf['override_title'] == TRUE ) {
      $block->title = $conf['override_title_text'];
    }
    else {
      $block->title = NULL;
    }
 
    $nid_match = array();
    preg_match('/\[id: (\d*?)\]$/', $conf['nid'], $nid_match);
    $node = node_load($nid_match[1]);

    $block->content = node_view($node, 'teaser');
 
    return $block;
  }
  return NULL;*/
}