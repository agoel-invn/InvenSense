import boto3
import datetime
from elasticsearch import Elasticsearch, RequestsHttpConnection
import json
import logging
import math
import os
from requests_aws4auth import AWS4Auth
import sensor_handlers

logger = logging.getLogger()
logger.setLevel(logging.INFO)

host = os.environ["ELASTICSEARCH_HOST"]
region = os.environ["REGION"]
service = os.environ["SERVICE"]

credentials = boto3.Session().get_credentials()
awsauth = AWS4Auth(credentials.access_key, credentials.secret_key, region, service, session_token=credentials.token)

SENSOR_INDEX = os.environ["SENSOR_INDEX"]

elastic_search_service = Elasticsearch(
    hosts = [{'host': host, 'port': 443}],
    http_auth = awsauth,
    use_ssl = True,
    verify_certs = True,
    connection_class = RequestsHttpConnection
)

def lambda_handler(event, context):
    
    print(f"Event received on AWS Lambda: {event}")

    message_payload = json.loads(event)

    # Extract timestamp components from JSON
    epoch_sec = message_payload['header']['stamp']['sec']
    epoch_nanosec = message_payload['header']['stamp']['nanosec']

    # Convert to datetime
    datetime_obj = datetime.datetime.fromtimestamp(epoch_sec) + datetime.timedelta(microseconds=epoch_nanosec // 1000)

    # Format datetime string with nanosecond precision
    formatted_datetime = datetime_obj.strftime('%Y-%m-%d %H:%M:%S.%f')

    message_payload['str_timestamp'] = formatted_datetime
    message_payload['timestamp'] = datetime_obj

    message_payload = sensor_handlers.SensorEventHander().handle_event(sensor_type=message_payload['header']['frame_id'], message_payload=message_payload)
    elastic_search_service.index(index=SENSOR_INDEX, body=message_payload)