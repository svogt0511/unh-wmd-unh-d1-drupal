<?php

/**
 * @file
 *
 * @todo: Update this docblock.
 * @todo: make sure we get full output on other than 'short' informationLevel
 *
 * Functions for views php calls.  We are trying to minimize this.
 */

/*
 *
 * VIEW: TESTIMONIAL
 * DISPLAY: CONTENT PANE (In course page, testimonials tab, the signature - global php
 *  in views.)
 *
 *
 */
 function unh_d1_drupal_testimonialView_signature($nid) {
  $node = node_load($nid);

  $tmp_field_value =  field_get_items('node', $node, 'field_student_name');
  $student_name = $tmp_field_value[0]['value'];
  $tmp_field_value =  field_get_items('node', $node, 'field_student_title');
  $student_title = $tmp_field_value[0]['value'];
  $tmp_field_value =  field_get_items('node', $node, 'field_student_company');
  $student_company = $tmp_field_value[0]['value'];

  $output = '';
  $comma = FALSE;
  if (!empty($student_name)) {
    $output = $student_name;
    $comma = TRUE;
  }

  if (!empty($student_title)) {
    if ($comma) { $output .= ' &sdot; '; }
    $output .= $student_title;
    $comma = TRUE;
  }

  if (!empty($student_company)) {
    if ($comma) { $output .= ' &sdot; '; }
    $output .= $student_company;
  }

  if (!empty($output)) {
    $output ='<hr class="testimonial-stamp" />' . $output;
  }

  return $output;
}