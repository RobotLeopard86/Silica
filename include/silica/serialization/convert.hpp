#pragma once

#include "binary.hpp"
#include "json.hpp"
#include "yaml.hpp"

namespace silica::serialization {
	struct convert {	//NOLINT namespace like name
		struct to_json {//NOLINT namespace like name
			template<typename T>
			static Expected<std::string> from_yaml_string(std::string_view str) {
				Expected<T> yaml_out = yaml::from_string<T>(str);
				if(yaml_out.is_error()) return Expected<std::string>(yaml_out.error());
				T obj = yaml_out.unwrap();
				return json::to_string(&obj);
			}

			template<typename T>
			static Expected<std::string> from_yaml_stream(std::istream& stream) {
				Expected<T> yaml_out = yaml::from_string<T>(stream);
				if(yaml_out.is_error()) return Expected<std::string>(yaml_out.error());
				T obj = yaml_out.unwrap();
				return json::to_string(&obj);
			}

			template<typename T>
			static Expected<std::string> from_binary_vector(const std::vector<uint8_t>& vector) {
				Expected<T> binary_out = binary::from_vector<T>(vector);
				if(binary_out.is_error()) return Expected<std::string>(binary_out.error());
				T obj = binary_out.unwrap();
				return json::to_string(&obj);
			}

			template<typename T>
			static Expected<std::string> from_binary_stream(std::istream& stream) {
				Expected<T> binary_out = binary::from_vector<T>(stream);
				if(binary_out.is_error()) return Expected<std::string>(binary_out.error());
				T obj = binary_out.unwrap();
				return json::to_string(&obj);
			}
		};
		struct to_yaml {//NOLINT namespace like name
			template<typename T>
			static Expected<std::string> from_json_string(std::string_view str) {
				Expected<T> json_out = json::from_string<T>(str);
				if(json_out.is_error()) return Expected<std::string>(json_out.error());
				T obj = json_out.unwrap();
				return yaml::to_string(&obj);
			}

			template<typename T>
			static Expected<std::string> from_json_stream(std::istream& stream) {
				Expected<T> json_out = json::from_string<T>(stream);
				if(json_out.is_error()) return Expected<std::string>(json_out.error());
				T obj = json_out.unwrap();
				return yaml::to_string(&obj);
			}

			template<typename T>
			static Expected<std::string> from_binary_vector(const std::vector<uint8_t>& vector) {
				Expected<T> binary_out = binary::from_vector<T>(vector);
				if(binary_out.is_error()) return Expected<std::string>(binary_out.error());
				T obj = binary_out.unwrap();
				return yaml::to_string(&obj);
			}

			template<typename T>
			static Expected<std::string> from_binary_stream(std::istream& stream) {
				Expected<T> binary_out = binary::from_vector<T>(stream);
				if(binary_out.is_error()) return Expected<std::string>(binary_out.error());
				T obj = binary_out.unwrap();
				return yaml::to_string(&obj);
			}
		};
		struct to_binary {//NOLINT namespace like name
			template<typename T>
			static Expected<std::vector<uint8_t>> from_json_string(std::string_view str) {
				Expected<T> json_out = json::from_string<T>(str);
				if(json_out.is_error()) return Expected<std::vector<uint8_t>>(json_out.error());
				T obj = json_out.unwrap();
				return binary::to_vector(&obj);
			}

			template<typename T>
			static Expected<std::vector<uint8_t>> from_json_stream(std::istream& stream) {
				Expected<T> json_out = json::from_string<T>(stream);
				if(json_out.is_error()) return Expected<std::vector<uint8_t>>(json_out.error());
				T obj = json_out.unwrap();
				return binary::to_vector(&obj);
			}

			template<typename T>
			static Expected<std::vector<uint8_t>> from_yaml_string(std::string_view str) {
				Expected<T> yaml_out = yaml::from_string<T>(str);
				if(yaml_out.is_error()) return Expected<std::vector<uint8_t>>(yaml_out.error());
				T obj = yaml_out.unwrap();
				return binary::to_vector(&obj);
			}

			template<typename T>
			static Expected<std::vector<uint8_t>> from_yaml_stream(std::istream& stream) {
				Expected<T> yaml_out = yaml::from_string<T>(stream);
				if(yaml_out.is_error()) return Expected<std::vector<uint8_t>>(yaml_out.error());
				T obj = yaml_out.unwrap();
				return binary::to_vector(&obj);
			}
		};
	};
}