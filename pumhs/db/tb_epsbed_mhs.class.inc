<?php
require_once 'default_table.class.inc';
class tb_epsbed_mhs extends Default_Table
{
    // additional class variables go here
    function __construct ()
    {
        $this->tablename       = 'msmhs';
        
		$this->fieldlist       = array('nimhsmsmhs','nmmhsmsmhs');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['nimhsmsmhs'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>

