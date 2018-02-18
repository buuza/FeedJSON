<?php

function show_feed_json() {
  
    //get type of content from the link, return articles by default
    $type = (empty(arg(1))) ? 'article' : arg(1);
    //limit number of nodes returned by user, 1000 by default
    $limit = (arg(2) > 0) ? arg(2) : 1000;

    //Use Database API to retrieve current posts.
    $query = db_select('node', 'n')
        ->fields('n', array('nid', 'type', 'title', 'created', 'changed', 'uid', 'status'))
        ->condition('status', 1)
        ->condition('type', $type)
        ->orderBy('created', 'DESC')
        ->range(0, $limit)
        ->execute();

    $articles = array();
      
    foreach ($query as $node) {
        $article['nid'] = $node->nid;
        $article['title'] = $node->title;
        $article['created'] = date("Y-m-d", $node->created);
        $article['updated'] = date("Y-m-d", $node->changed);
        $article['status'] = $node->status;
        //$article['type'] = $node->type;
        $article['uid'] = $node->uid;
        $article['username'] = user_load($node->uid)->name;
        $article['link'] = url('node/' . $node->nid, array('absolute' => TRUE));
        $articles[] = $article;
    }
    
    // ../feed/
    //return drupal_json_output($articles);
    return json_encode($articles, JSON_UNESCAPED_SLASHES);
}