<?php
  $output = '';
  $form_state = $variables['form_state'];
  $filtered = $variables['filtered'];

  if (empty($form_state["storage"]["results"])) {
    $str = unh_d1_drupal_get_search_no_results_text() . unh_d1_drupal_get_search_again_button() . PHP_EOL;
  } else {
  
    $str = '
<div name="search-results" class="search-results">';
    foreach ($form_state["storage"]["results"]["filter"] as $filter) {
      $str .= '
  <div class="search-area">
    <div class="search-area-header h2">' . $filter['filter_title'] . '</div>
    <div class="search-area-body">';

      $str .= unh_d1_drupal_get_courseListBlock_markup($filter['courseProfiles']);

      $str .= '
    </div>
  </div>';
    }

    $str .= '
</div>';

    $str = unh_d1_drupal_get_search_again_button('top-of-page') . $str .  unh_d1_drupal_get_backToTop_button('search-results');
  }

  $output = $str;
?>

<?=$output?>
