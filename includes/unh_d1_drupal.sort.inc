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
 * Functions for sorting things.
 *
 ******************************************************************************/

/**
 * Given a list of sections, returns them sorted by semester/start date/section title.
 * 
 */
function unh_d1_drupal_sort_rr_sections($sections = array(), 
  $sort_option = UNH_D1_DRUPAL_BODY_SECTIONS_SORT_BY_SECTION_DATE_THEN_TITLE, 
  $sort_direction = UNH_D1_DRUPAL_BODY_SECTIONS_SORT_ASCENDING) 
{
  $ret = array();
  
  if (!empty($sections)) {
    // $ret = unh_d1_client_sort_sections_by_semesterStartDateSectionTitle($sections);
    if ($sort_option == UNH_D1_DRUPAL_BODY_SECTIONS_SORT_BY_SECTION_DATE_THEN_TITLE) {  
      $ret = unh_d1_client_sort_sections_by_startDateSectionTitle($sections, $sort_direction);
    } elseif ($sort_option == UNH_D1_DRUPAL_BODY_SECTIONS_SORT_BY_SECTION_TITLE) {
      $ret = unh_d1_client_sort_sections_by_semesterSectionTitle($sections, $sort_direction);
    } else {
      
    }
  }
  
  return $ret;
}