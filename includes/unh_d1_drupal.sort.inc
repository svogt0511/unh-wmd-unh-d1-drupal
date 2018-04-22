<?php

/**
 * @file
 *
 * @todo: Update this docblock.
 * @todo: make sure we get full output on other than 'short' informationLevel
 *
 * Functions mainly for sorting things.
 */

/******************************************************************************
 *
 * Calls for sorting things.
 *
 ******************************************************************************/

/**
 * Given a list of sections, returns them sorted by semester/start date/section title.
 * 
 */
function unh_d1_drupal_sort_rr_sections($sections = array()) {
  $ret = array();
  
  if (!empty($sections)) {  
    // $ret = unh_d1_client_sort_sections_by_semesterStartDateSectionTitle($sections);
    // $ret = unh_d1_client_sort_sections_by_semesterSectionTitle($sections);
    // $ret = unh_d1_client_sort_sections_by_startDateSectionTitle($sections);
    $ret = unh_d1_client_sort_sections_by_sectionTitle($sections);
  }
  
  return $ret;
}