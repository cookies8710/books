- publish/subscribe pattern

- kafka is ditributed commit log

- message
	- unit of data
	- just an array of bytes
	- optional metadata "key", which is again just an array of bytes
	- written in batches

- schema
	- message structure description (e.g. JSON, XML, etc.)
	- see Apache Avro for robust schema handling (versioning, ...)
