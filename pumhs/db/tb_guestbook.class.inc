<?php
require_once 'default_table.class.inc';
class tb_guestbook extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'guestbook';
        
		$this->fieldlist       = array('id','name','email','comment','datetime');
        
		$this->sql_orderby         = 'datetime';
		
		$this->fieldlist['id'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>