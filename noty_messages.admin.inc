<?php

/**
 * Implements hook_settings().
 * Configuration settings page.
 *
 * @return
 *    Array of the system settings form.
 */
function noty_messages_settings() {
  $module_path = drupal_get_path('module', 'noty_messages');
  dsm('something');
  if (!libraries_get_path('noty')){
    $form['noty_messages_code_status'] = array(
      '#type' => 'fieldset',
      '#title' => t('noty Messages settings'),
      '#weight' => -10,
      '#description' => t('Please install noty'),
    );
    return $form;
  }
  $form['noty_messages_code_status'] = array(
  '#type' => 'fieldset',
  '#title' => t('noty Messages settings'),
  '#weight' => -10,
  );
  return $form;
}
