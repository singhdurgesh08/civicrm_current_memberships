<?php

/**
  @file
 * civicrm_current_memberships_listing.inc
 * Implementation of civicrm_current_memberships_listing().
 *
 * In this hook, We are Showing CiviCRM Membership Search and list
 * For Now we are adding Simple Search and list if it is required  
 * we can make it More Better Way
 * For Example : Using Datatable OR Angular Extension
 * @return
 *   An Table With List and search.
 */
function civicrm_current_memberships_listing() {
# configure the table header columns
    $header = array(
        array('data' => t('ID'), 'field' => 'm.id', 'sort' => 'ASC'),
        array('data' => t('Contact ID'), 'field' => 'm.contact_id', 'sort' => 'ASC'),
        array('data' => t('Member Ship Type Id'), 'field' => 'm.membership_type_id', 'sort' => 'ASC'),
        array('data' => t('Join Date'), 'field' => 'm.join_date', 'sort' => 'ASC'),
        array('data' => t('Start Date'), 'field' => 'm.start_date', 'sort' => 'ASC'),
        array('data' => t('End Date'), 'field' => 'm.end_date', 'sort' => 'ASC'),
        array('data' => t('Source'), 'field' => 'm.source', 'sort' => 'ASC'),
    );
    #Set Page Limit
    $pagelimit = !empty($_GET['items_per_page']) ? $_GET['items_per_page'] : 20;
    #Get Query
    $contactid = !empty($_GET['contactid']) ? $_GET['contactid'] : '';

    if ($pagelimit) {
        $items_per_page = $pagelimit;
    } else {
        $items_per_page = 20;
    }

    if ($contactid) {
        # For Now we are Showing list from one table
        # We can make it multiple table As per Required
        $query = db_select('civicrm_membership', 'm')->fields('m', array('id', 'contact_id', 'membership_type_id', 'join_date', 'start_date',
                    'end_date', 'source'))->condition('m.contact_id', $contactid, '=');
        
        // To Do Better Query
        $result = $query->execute();
        
        
    } else {
        $query = db_select('civicrm_membership', 'm')->
                fields('m', array('id', 'contact_id', 'membership_type_id', 'join_date', 'start_date', 'end_date', 'source'));
        // To Do Better Query
        $result = $query->execute();
    }
    #Coloum Set
    $rows = array();
    foreach ($result as $row) {
        $rows[] = array(
            array('data' => $row->id),
            array('data' => $row->contact_id),
            array('data' => $row->membership_type_id),
            array('data' => $row->join_date),
            array('data' => $row->start_date),
            array('data' => $row->end_date),
            array('data' => $row->source),
        );
    }
    # add the pager
    $output = '';
    $output .= render(drupal_get_form('civicrm_current_memberships_form'));
    $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('views-table')), 'empty' => 'No results found'));
    $output .= theme('pager');

    return $output;
}
