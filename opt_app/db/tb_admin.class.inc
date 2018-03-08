<?php
require_once 'default_table.class.inc';
class tb_admin extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'tmst_admin';
        
		$this->fieldlist       = array('id_admin','user','pass');
        
		$this->sql_orderby         = 'user';
		
		$this->fieldlist['id_admin'] = array('pkey' => 'y');
		$this->fieldlist['user'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>